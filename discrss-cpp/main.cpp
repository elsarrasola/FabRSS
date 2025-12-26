#include <dpp/dpp.h>
#include "env.h"
#include "commands.h"

int main() {
    dpp::cluster bot(env::BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event){
        if(event.command.get_command_name() == "ping") {
            event.reply(commands::ping());
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if(dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping command for testing your setup !", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);
}
