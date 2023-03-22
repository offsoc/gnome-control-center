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

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define CC_TYPE_ACCENT_COLOR (cc_accent_color_get_type ())
G_DECLARE_FINAL_TYPE (CcAccentColor, cc_accent_color, CC, ACCENT_COLOR, GtkWidget)

GtkWidget *      cc_accent_color_new              (AdwAccentColor color);

AdwAccentColor * cc_accent_color_get_accent_color (CcAccentColor *self);

G_END_DECLS
