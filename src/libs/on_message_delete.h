#pragma once

#include <concord/discord.h>
#include <concord/cog-utils.h>
#include "bot_include.h"

void on_message_delete(struct discord *client, const struct discord_message_delete *event);
