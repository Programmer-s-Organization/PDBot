#pragma once

#include <sqlite3.h>
#include <orca/discord.h>
#include <orca/orka-utils.h>
#include "config.h"

void add_message_db(const struct discord_message *message);
