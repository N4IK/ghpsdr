/** 
* @file bandscope_update.c
* @brief Bandscope Update files.
* @author John Melton, G0ORX/N6LYT, Doxygen Comments Dave Larsen, KV0S
* @version 0.1
* @date 2009-04-11
*/

/* Copyright (C) 
* 2009 - John Melton, G0ORX/N6LYT, Doxygen Comments Dave Larsen, KV0S
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
*/

#include <gtk/gtk.h>

#include <wdsp.h>
#include "main.h"
#include "bandscope.h"
#include "bandscope_update.h"
#include "channel.h"

int updatingBandscope;
int bandscopeUpdatesPerSecond=BANDSCOPE_UPDATES_PER_SECOND;

gint bandscopeUpdate(gpointer data);
void bandscopeUpdateSamples();

float bandscopeSamples[bandscopeWIDTH*2];

gint bandscopeTimerId;

/* --------------------------------------------------------------------------*/
/** 
* @brief New bandscope update.
*/
void newBandscopeUpdate() {
    bandscopeTimerId=gtk_timeout_add(1000/bandscopeUpdatesPerSecond,bandscopeUpdate,NULL);
}

/* --------------------------------------------------------------------------*/
/** 
* @brief Stop the bandscope update. 
*/
void stopBandscopeUpdate() {
    gtk_timeout_remove(bandscopeTimerId);
}

/* --------------------------------------------------------------------------*/
/** 
* @brief Bandscope update 
* 
* @param data
* 
* @return  
*/
gint bandscopeUpdate(gpointer data) {
    bandscopeUpdateSamples();
    return TRUE;
}

/* --------------------------------------------------------------------------*/
/** 
* @brief Bandscope Sample update. 
*/
void bandscopeUpdateSamples() {
    int result;
    GetPixels(CHANNEL_BS, 0, bandscopeSamples, &result);
    updateBandscope(bandscopeSamples);
}
