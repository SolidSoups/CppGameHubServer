//
// Created by wiley on 3/6/2025.
//
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio> // For popen and pclose
#include <ranges>
#include <utility>

using namespace std;

int RunServerCommand(const std::string& command, std::string& output)
{
	// prepare command
	std::string execCmd = "..\\GameHub.exe " + command;

	// Run command and capture output
	FILE* pipe = popen(execCmd.c_str(), "r");
	if (!pipe)
	{
		std::cerr << "Failed to run command! popen() returned nullptr." << std::endl;
		return -1;
	}

	char buffer[128];
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
	{
		output += buffer;
	}
	pclose(pipe); // Close the pipe
	return 0;
}

class GameHubCommandTest : public ::testing::TestWithParam<std::pair<std::string, std::string>>
{
};

TEST_P(GameHubCommandTest, RunCommandAndCheckOutput)
{
	auto param = GetParam();
	std::string mainCommand = param.first;
	std::string expectedOutput = param.second;

	std::string output = "";
	int result = RunServerCommand(mainCommand, output);

	ASSERT_EQ(result, 0) << "Command execution failed: \n" << mainCommand;

	EXPECT_NE(output.find(expectedOutput), std::string::npos)
	<< "Command run: " << mainCommand << "\n"
	<< "Expected output not found: \n" << expectedOutput << "\nOutput found: \n" << output;
}

std::string joinVector(const std::vector<std::string>& foo)
{
	std::stringstream ss;
	for (int i = 0; i < foo.size(); i++)
	{
		ss << foo[i] << "\n";
	}
	return ss.str();
}

INSTANTIATE_TEST_SUITE_P(
	TestDatabase, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me@test.com pass123", R"(create_database
200)"),
		std::make_pair("create_database", R"(create_database
400)"),
		std::make_pair("create_database me@test.com", R"(create_database
400)"),
		std::make_pair("create_database me3@test.com pass123", R"(create_database
200)"),
		std::make_pair("login me@test.com pass123", R"(login
401)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestLogin, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me2@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me2@test.com pass123", R"(login
401)"),
		std::make_pair("login me2@test.com", R"(login
400)"),
		std::make_pair("login me2@test.com pass111", R"(login
200)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestAddAdmin, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_admin pass321", R"(login
200

add_admin
400)"),
		std::make_pair("login me4@test.com pass111 add_admin me5@test.com pass321", R"(login
200

add_admin
201)"),
		std::make_pair("login me5@test.com pass321", R"(login
200)"),
		std::make_pair("login me5@test.com pass321 add_admin me5@test.com pass321", R"(login
200

add_admin
409)"),
		std::make_pair("add_admin me5@test.com pass321", R"(add_admin
403)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestRemoveAdmin, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_admin me5@test.com pass321 remove_user me4@test.com", R"(login
200

add_admin
201

remove_user
200)"),
		std::make_pair("login me4@test.com pass111", R"(login
401)"),
		std::make_pair("login me5@test.com pass321 remove_user", R"(login
200

remove_user
400)"),
		std::make_pair("login me5@test.com pass321 remove_user me44@test.com", R"(login
200

remove_user
404)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestGetUser, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_admin me5@test.com pass321 add_admin me6@test.com pass321 add_admin me7@test.com pass321 add_admin me8@test.com pass321 add_admin me9@test.com pass321", R"(login
200

add_admin
201

add_admin
201

add_admin
201

add_admin
201

add_admin
201)"),
		std::make_pair("get_users", R"(get_users
403)"),
		std::make_pair("login me4@test.com pass111 get_users", R"(login
200

get_users
200
1:me4@test.com
1:me5@test.com
1:me6@test.com
1:me7@test.com
1:me8@test.com
1:me9@test.com)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestAddGame, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_game", R"(login
200

add_game
400)"),
		std::make_pair("login me4@test.com pass111 add_game \"Snake Game\"", R"(login
200

add_game
201)"),
		std::make_pair("login me4@test.com pass111 add_game \"Snake Game\"", R"(login
200

add_game
409)"),
		std::make_pair("add_game \"Snake Game 2\"", R"(add_game
403)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestRemoveGame, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_game Maze remove_game Maze", R"(login
200

add_game
201

remove_game
200)"),
		std::make_pair("login me4@test.com pass111 remove_game", R"(login
200

remove_game
400)"),
		std::make_pair("login me4@test.com pass111 remove_game Maze 3", R"(login
200

remove_game
404)"),
		std::make_pair("login me4@test.com pass111 add_game Maze", R"(login
200

add_game
201)"),
		std::make_pair("remove_game Maze", R"(remove_game
403)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestGetGames, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_game Snake1 add_game Snake2 add_game Snake3 add_game Snake4", R"(login
200

add_game
201

add_game
201

add_game
201

add_game
201)"),
		std::make_pair("get_games", R"(get_games
403)"),
		std::make_pair("login me4@test.com pass111 get_games", R"(login
200

get_games
200
Snake1
Snake2
Snake3
Snake4)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestLoginPlayer, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("add_player player@test.com pass123", R"(add_player
201)"),
		std::make_pair("login_player", R"(login_player
400)"),
		std::make_pair("login_player me4@test.com", R"(login_player
401)"),
		std::make_pair("login_player player@test.com pass123", R"(login_player
200)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestAddPlayer, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("add_player", R"(add_player
400)"),
		std::make_pair("add_player player@test.com", R"(add_player
400)"),
		std::make_pair("add_player player@test.com pass123", R"(add_player
201)"),
		std::make_pair("add_player player@test.com pass123", R"(add_player
409)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestBuyGame, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("login me4@test.com pass111 add_game Snake add_game Pokemon", R"(login
200

add_game
201

add_game
201)"),
		std::make_pair("add_player player@test.com pass123", R"(add_player
201)"),
		std::make_pair("buy_game Snake", R"(buy_game
403)"),
		std::make_pair("login_player player@test.com buy_game", R"(login_player
200

buy_game
400)"),
		std::make_pair("login_player player@test.com buy_game Snakes", R"(login_player
200

buy_game
404)"),
		std::make_pair("login_player player@test.com buy_game Snake buy_game Pokemon", R"(login_player
200

buy_game
200

buy_game
200)")
	)
);

INSTANTIATE_TEST_SUITE_P(
	TestGetOwnedGames, GameHubCommandTest,
	::testing::Values(
		std::make_pair("create_database me4@test.com pass111", R"(create_database
200)"),
		std::make_pair("add_player player@test.com pass123", R"(add_player
201)"),
		
		std::make_pair("login me4@test.com pass111 add_game Pokemon add_game Minecraft add_game \"Metal Gear Solid\"", R"(login
200

add_game
201

add_game
201

add_game
201)"),
		std::make_pair("login_player player@test.com buy_game Pokemon buy_game Minecraft buy_game \"Metal Gear Solid\"", R"(login_player
200

buy_game
200

buy_game
200

buy_game
200)"),
		std::make_pair("get_owned_games", R"(get_owned_games
403)"),
		std::make_pair("login_player player@test.com get_owned_games", R"(login_player
200

get_owned_games
200
Pokemon
Minecraft
Metal Gear Solid)")
	)
);

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	// Enable std::cout output
	::testing::GTEST_FLAG(output) = "direct";

	std::cout << "Custom main() is running!" << std::endl;

	return RUN_ALL_TESTS();
}
