#include <orca/discord.h>
#include <orca/orka-utils.h>
#include "../libs/config.h"

void on_message_delete(struct discord *client, const struct discord_user *bot, const u64_snowflake_t id, const u64_snowflake_t channel_id, const u64_snowflake_t guild_id) {
    struct discord_embed *embed = discord_embed_alloc();
    struct discord_create_message_params params = {.embed = embed};
    embed->color = 14423100;
    embed->timestamp = orka_timestamp_ms();

    discord_create_message(client, C_LOG, &params, NULL);
    discord_embed_free(embed);

    return;
}
