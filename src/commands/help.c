#include <orca/discord.h>
#include <orca/orka-utils.h>
#include "../libs/load_embed_from_json.h"

void help(struct discord *client, const struct discord_user *user, const struct discord_message *msg) {
    if (msg->author->bot) return;

    struct discord_embed *embed = load_embed_from_json("src/json/help.json");
    struct discord_create_message_params params = {.embed = embed};

    embed->author = (struct discord_embed_author*)msg->author;
    embed->timestamp = orka_timestamp_ms();
    
    discord_create_message(client, msg->channel_id, &params, NULL);

    return;
}
