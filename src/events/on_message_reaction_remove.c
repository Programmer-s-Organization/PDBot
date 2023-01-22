#include <concord/discord.h>
#include <concord/cog-utils.h>
#include "../libs/bot_include.h"

void on_message_reaction_remove(struct discord *client, const struct discord_message_reaction_remove *event) {
    struct discord_user member;
    struct discord_ret_user ret_member = {.sync = &member};
    discord_user_init(&member);
    discord_get_user(client, event->user_id, &ret_member);

    if (member.bot) {
        discord_user_cleanup(&member);
        return;
    }

    char message_id_str[ID_STR_LEN], channel_id_str[ID_STR_LEN], channel_str[CHANNEL_MENTION_LEN], author_id_str[ID_STR_LEN], author_str[USER_MENTION_LEN], username_and_discriminator[USER_AND_DESCRIM_LEN], emoji_str[emoji_mention_len(event->emoji)], footer_text[ID_STR_LEN+11];
    char *avatar_url = malloc(AVATAR_URL_LEN);
    struct discord_message message;
    struct discord_embed embed;
    struct discord_ret_message ret_message = {.sync = &message};
    discord_message_init(&message);
    discord_embed_init(&embed);
    struct discord_create_message params = {
        .embeds = &(struct discord_embeds) {
            .size = 1,
            .array = &embed
        }
    };

    message.guild_id = event->guild_id;
    embed.timestamp = discord_timestamp(client);
    embed.color = COLOR_PINK_PANTONE;

    get_avatar_url(avatar_url, &member);
    id_to_str(message_id_str, event->message_id);
    id_to_str(channel_id_str, event->channel_id);
    channel_mention(channel_str, event->channel_id);
    id_to_str(author_id_str, member.id);
    user_mention(author_str, member.id);
    username_and_discriminator_to_str(username_and_discriminator, &member);
    emoji_mention(emoji_str, event->emoji);

    discord_get_channel_message(client, event->channel_id, event->message_id, &ret_message);
    discord_embed_set_title(&embed, "Reaction removed by %s %s", username_and_discriminator, emoji_str);
    discord_embed_set_author(&embed, member.username, NULL, avatar_url, NULL);
    discord_embed_set_thumbnail(&embed, avatar_url, NULL, AVATAR_HEIGHT, AVATAR_WIDTH);
    discord_embed_add_field(&embed, "Message ID", message_id_str, true);
    discord_embed_add_field(&embed, "Channel ID", channel_id_str, true);
    discord_embed_add_field(&embed, "Author ID", author_id_str, true);
    discord_embed_add_field(&embed, "Channel", channel_str, false);
    discord_embed_add_field(&embed, "Author", author_str, true);
    discord_embed_add_field(&embed, "Content", message.content, false);
    snprintf(footer_text, sizeof(footer_text), "Author ID: %lu", member.id);
    discord_embed_set_footer(&embed, footer_text, avatar_url, NULL);

    discord_create_message(client, C_LOG, &params, NULL);

    free(avatar_url);
    discord_embed_cleanup(&embed);
    discord_message_cleanup(&message);

    return;
}
