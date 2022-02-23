#include <concord/discord.h>
#include "../libs/bot_include.h"

void on_voice_state_update(struct discord *client, const struct discord_voice_state *vs) {
    struct discord_guild_member guild_member;
    struct discord_ret_guild_member ret_guild_member = {.sync = &guild_member};
    discord_guild_member_init(&guild_member);
    discord_get_guild_member(client, vs->guild_id, vs->user_id, &ret_guild_member);

    if (vs->channel_id) {
        switch (vs->channel_id) {
            case VC_CHAT_ONE: {
                if (!guild_member_has_role(&guild_member, R_VC_CHAT_ONE)) discord_add_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_ONE, NULL);
                if (guild_member_has_role(&guild_member, R_VC_CHAT_TWO)) discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_TWO, NULL);
                if (guild_member_has_role(&guild_member, R_VC_MUSIC)) discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_MUSIC, NULL);
                break;
            }
            case VC_CHAT_TWO: {
                if (!guild_member_has_role(&guild_member, R_VC_CHAT_TWO)) discord_add_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_TWO, NULL);
                if (guild_member_has_role(&guild_member, R_VC_CHAT_ONE)) discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_ONE, NULL);
                if (guild_member_has_role(&guild_member, R_VC_MUSIC)) discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_MUSIC, NULL);
                break;
            }
            case VC_MUSIC: {
                if (!guild_member_has_role(&guild_member, R_VC_MUSIC)) discord_add_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_MUSIC, NULL);
                if (guild_member_has_role(&guild_member, R_VC_CHAT_ONE)) discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_ONE, NULL);
                if (guild_member_has_role(&guild_member, R_VC_CHAT_TWO)) discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_TWO, NULL);
                break;   
            }
            default: break;
        }
    }
    else {
        for (size_t i=0; i<vs->member->roles->size; i++) {
            switch (vs->member->roles->array[i]) {
                case R_VC_CHAT_ONE: discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_ONE, NULL); break;
                case R_VC_CHAT_TWO: discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_CHAT_TWO, NULL); break;
                case R_VC_MUSIC: discord_remove_guild_member_role(client, vs->guild_id, vs->user_id, R_VC_MUSIC, NULL); break;
                default: break;
            }
        }
    }

    discord_guild_member_cleanup(&guild_member);

    return;
}
