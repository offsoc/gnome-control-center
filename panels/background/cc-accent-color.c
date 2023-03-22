/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2023 Jamie Murphy <jmurphy@gnome.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <config.h>

#include "cc-accent-color.h"

#define INTERFACE_PATH_ID "org.gnome.desktop.interface"

struct _CcAccentColor
{
  GtkWidget       parent_instance;

  AdwAccentColor  color;
};

enum
{
  PROP_0,
  PROP_ACCENT_COLOR,
  N_PROPS
};

static GParamSpec *props[N_PROPS];

G_DEFINE_FINAL_TYPE (CcAccentColor, cc_accent_color, GTK_TYPE_WIDGET)

static void
cc_accent_color_get_property (GObject    *object,
                              guint       prop_id,
                              GValue     *value,
                              GParamSpec *pspec)
{
  CcAccentColor *self = CC_ACCENT_COLOR (object);

  switch (prop_id)
    {
    case PROP_ACCENT_COLOR:
      g_value_set_enum (value, self->color);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
cc_accent_color_set_property (GObject      *object,
                              guint         prop_id,
                              const GValue *value,
                              GParamSpec   *pspec)
{
  CcAccentColor *self = CC_ACCENT_COLOR (object);

  switch (prop_id)
    {
    case PROP_ACCENT_COLOR:
      self->color = g_value_get_enum (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
cc_accent_color_snapshot (GtkWidget   *widget,
                          GtkSnapshot *snapshot)
{
  CcAccentColor *self = CC_ACCENT_COLOR (widget);
  AdwStyleManager *style_manager = adw_style_manager_get_default ();
  gboolean is_dark = adw_style_manager_get_dark (style_manager);
  GdkRGBA color = { 0, 0, 0, 0 };
  GtkAllocation allocation;

  gtk_widget_get_allocation (widget, &allocation);

  if (is_dark)
    adw_accent_color_to_rgba (self->color, NULL, &color);
  else
    adw_accent_color_to_rgba (self->color, &color, NULL);

  gtk_snapshot_save (snapshot);

  gtk_snapshot_append_color (snapshot, &color,
                             &GRAPHENE_RECT_INIT (0.0f, 0.0f,
                                                  allocation.width, allocation.height));

  gtk_snapshot_restore (snapshot);
}

static void
cc_accent_color_class_init (CcAccentColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->get_property = cc_accent_color_get_property;
  object_class->set_property = cc_accent_color_set_property;
  widget_class->snapshot = cc_accent_color_snapshot;

  props[PROP_ACCENT_COLOR] =
    g_param_spec_enum ("accent-color", "", "",
                       ADW_TYPE_ACCENT_COLOR, ADW_ACCENT_COLOR_DEFAULT,
                       G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, props);
  gtk_widget_class_set_layout_manager_type (widget_class, GTK_TYPE_BIN_LAYOUT);
}

static void
cc_accent_color_init (CcAccentColor *self)
{
}

GtkWidget *
cc_accent_color_new (AdwAccentColor color)
{
  return g_object_new (CC_TYPE_ACCENT_COLOR,
                       "accent-color", color,
                       NULL);
}

AdwAccentColor *
cc_accent_color_get_accent_color (CcAccentColor *self)
{
  g_return_val_if_fail (CC_IS_ACCENT_COLOR (self), NULL);

  return &self->color;
}
