#ifndef QUEENSIDE_SERVICE_GAMESYNC_HPP
# define QUEENSIDE_SERVICE_GAMESYNC_HPP

#include <unordered_map>
#include <optional>

#include "GameMaster.hpp"
#include "IDGenerator.hpp"

/**
**
**	Gamesync class
**
**	Used to create and managing gamemasters.
*/
namespace Queenside {
	class Gamesync {
		public:
			static Gamesync *getInstance();

			const std::optional<std::string> findGameMaster(const std::string&);

			std::string createGameMaster(const std::string&, const std::string&);
			void removeGameMaster(const std::string&);

			const std::string idToGameMaster(const std::string &, const std::string &, const std::string&);
			const std::string uciokToGameMaster(const std::string&, const std::string&, const std::string&);
			const std::string readyokToGameMaster(const std::string&, const std::string&, const std::string&);
			const std::string bestmoveToGameMaster(const std::string&, const std::string&, const std::string&);
			const std::string infoToGameMaster(const std::string&, const std::string&, const std::string&);
			const GameMaster &getGameMaster(const std::string&);
		private:
			Gamesync() = default;
			static Gamesync *_singleton;

			std::unordered_map<std::string, GameMaster> _gamemasters;
	};
};

#endif /* !QUEENSIDE_SERVICE_GAMESYNC_HPP */