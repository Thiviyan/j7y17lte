/*
 *  Copyright (C) 2012, Samsung Electronics Co. Ltd. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */
#include "../ssp.h"
#include "ssp_factory.h"

/*************************************************************************/
/* factory Sysfs                                                         */
/*************************************************************************/
static ssize_t light_name_show(struct device *dev,
                               struct device_attribute *attr, char *buf)
{
	struct ssp_data *data = dev_get_drvdata(dev);
	return data->light_ops->get_light_name(buf);
}

static ssize_t light_vendor_show(struct device *dev,
                                 struct device_attribute *attr, char *buf)
{
	struct ssp_data *data = dev_get_drvdata(dev);
	return data->light_ops->get_light_vendor(buf);
}

static ssize_t light_lux_show(struct device *dev,
                              struct device_attribute *attr, char *buf)
{
	struct ssp_data *data = dev_get_drvdata(dev);
	return data->light_ops->get_lux(data, buf);
}

static ssize_t light_data_show(struct device *dev,
                               struct device_attribute *attr, char *buf)
{
	struct ssp_data *data = dev_get_drvdata(dev);
	return data->light_ops->get_light_data(data, buf);
}

static ssize_t light_coef_show(struct device *dev,
                               struct device_attribute *attr, char *buf)
{
	struct ssp_data *data = dev_get_drvdata(dev);
	int ret = 0;

	ret = data->light_ops->get_light_coefficient(data, buf);

	return ret;
}

static DEVICE_ATTR(name, S_IRUGO, light_name_show, NULL);
static DEVICE_ATTR(vendor, S_IRUGO, light_vendor_show, NULL);
static DEVICE_ATTR(lux, S_IRUGO, light_lux_show, NULL);
static DEVICE_ATTR(raw_data, S_IRUGO, light_data_show, NULL);
static DEVICE_ATTR(coef, S_IRUGO, light_coef_show, NULL);

static struct device_attribute *light_attrs[] = {
	&dev_attr_name,
	&dev_attr_vendor,
	&dev_attr_lux,
	&dev_attr_raw_data,
	&dev_attr_coef,
	NULL,
};

void initialize_light_factorytest(struct ssp_data *data)
{
#if defined(CONFIG_SENSORS_SSP_LIGHT_TMD3700)
	light_tmd3700_function_pointer_initialize(data);
#elif defined(CONFIG_SENSORS_SSP_LIGHT_TMD3725)
	light_tmd3725_function_pointer_initialize(data);
#else
	light_tmg399x_function_pointer_initialize(data);
#endif

	sensors_register(data->devices[SENSOR_TYPE_LIGHT], data, light_attrs,
	                 "light_sensor");
}

void remove_light_factorytest(struct ssp_data *data)
{
	sensors_unregister(data->devices[SENSOR_TYPE_LIGHT], light_attrs);
}
