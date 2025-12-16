#include <dpp/dpp.h>
#include <env.h>

int main() {
    dpp::cluster bot(env::BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event){
        if(event.command.get_command_name() == "pingcpp") {
            event.reply("Pong !");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if(dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("pingcpp", "Ping pong ding dong !", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);
}
