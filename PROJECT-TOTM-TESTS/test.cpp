#include "stdafx.h"
#include "dummy_state.h"
#include "context.h"


# define EXPECT_NO_CRASH(statement) \
   EXPECT_EXIT((statement,exit(0)),::testing::ExitedWithCode(0),".*")

TEST(Stateman, PoppingOrReplacingWhenEmpty) {
	stateman test_state_stack;
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	test_state_stack.Popcurrent();
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	int test_me;
	test_state_stack.Add(std::make_unique<dummy_state>(test_me), true);
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 1);
}
TEST(Stateman,InitOfState) {
	stateman test_state_stack;
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	int test_me;
	test_state_stack.Add(std::make_unique<dummy_state>(test_me), true);
	EXPECT_EQ(test_me, dummy_state::code_types::Constructed);
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_me, dummy_state::code_types::Initialized_or_running);
}
TEST(Stateman,MultipleAddCommandsIn1Cycle) {
	stateman test_state_stack;
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	int test_me,test_me_2;
	test_state_stack.Add(std::make_unique<dummy_state>(test_me));
	test_state_stack.Add(std::make_unique<dummy_state>(test_me_2));
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 1);
	EXPECT_EQ(test_me, dummy_state::code_types::Destructed);
	EXPECT_EQ(test_me_2, dummy_state::code_types::Initialized_or_running);
}

TEST(Stateman, MultiplePopCommandsIn1Cycle) {
	stateman test_state_stack;
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	int test_me,test_me_2;
	test_state_stack.Add(std::make_unique<dummy_state>(test_me));
	test_state_stack.ProcessStatechange();
	test_state_stack.Add(std::make_unique<dummy_state>(test_me_2));
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 2);
	test_state_stack.Popcurrent();
	test_state_stack.Popcurrent();
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 1);
	EXPECT_EQ(test_me, dummy_state::code_types::Initialized_or_running);
	EXPECT_EQ(test_me_2, dummy_state::code_types::Destructed);

}

TEST(Stateman, AddAndPopCommandsIn1Cycle) {
	stateman test_state_stack;
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	int test_me,test_me_2;
	test_state_stack.Add(std::make_unique<dummy_state>(test_me));
	test_state_stack.ProcessStatechange();
	test_state_stack.Add(std::make_unique<dummy_state>(test_me_2));
	test_state_stack.Popcurrent();
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 1);
	EXPECT_EQ(test_me, dummy_state::code_types::Destructed);
	EXPECT_EQ(test_me_2, dummy_state::code_types::Initialized_or_running);
}

TEST(Stateman,IsLowerStatePaused) {
	stateman test_state_stack;
	EXPECT_EQ(test_state_stack.no_of_states(), 0);
	int test_me,test_me_2;
	test_state_stack.Add(std::make_unique<dummy_state>(test_me));
	test_state_stack.ProcessStatechange();
	test_state_stack.Add(std::make_unique<dummy_state>(test_me_2));
	test_state_stack.ProcessStatechange();
	EXPECT_EQ(test_state_stack.no_of_states(), 2);
	EXPECT_EQ(test_me, dummy_state::code_types::Paused);
	EXPECT_EQ(test_me_2, dummy_state::code_types::Initialized_or_running);
}

TEST(Assetholder_DeathTest, invalidgetfont) {
	asset_holder test_assets;
	EXPECT_DEATH(test_assets.get_font(0), "Assertion failed.*");
}

TEST(Assetholder_DeathTest, invalidgettexture) {
	asset_holder test_assets;
	EXPECT_DEATH(test_assets.get_texture(asset_holder::group_member_name::OJJAS,0), "Assertion failed.*");
}

TEST(Assetholder_DeathTest, invalidgetsoundbuffer) {
	asset_holder test_assets;
	EXPECT_DEATH(test_assets.get_soundbuffer(asset_holder::group_member_name::OJJAS, 0), "Assertion failed.*");
}

TEST(Assetholder_DeathTest, invalidplaysound) {
	asset_holder test_assets;
	EXPECT_DEATH(test_assets.play_sound(asset_holder::group_member_name::OJJAS, 0), "Assertion failed.*");
}

TEST(AssetholderProperLoading, validfont) {
	asset_holder test_assets;
	test_assets.add_font(0, "Fonts/Dosis-ExtraLight.otf");
	EXPECT_NO_CRASH(test_assets.get_font(0));
}

TEST(AssetholderProperLoading, validtexture) {
	asset_holder test_assets;
	test_assets.add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::SPRING, "Images/spring.png");
	EXPECT_NO_CRASH(test_assets.get_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::SPRING));
}

TEST(AssetholderProperLoading, validsoundbuffer) {
	asset_holder test_assets;
	test_assets.add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD, "Sounds/button_forward.flac");
	EXPECT_NO_CRASH(test_assets.get_soundbuffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD));
}

TEST(AssetholderProperLoading, validplaysound) {
	asset_holder test_assets;
	test_assets.add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD, "Sounds/button_forward.flac");
	EXPECT_NO_CRASH(test_assets.play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD));
}

TEST(AssetholderOverwrite, overwritefont) {
	asset_holder test_assets;
	test_assets.add_font( 0, "Fonts/Dosis-ExtraLight.otf" );
	test_assets.add_font( 0, "Fonts/Dosis-Light.otf");
	EXPECT_NO_CRASH(test_assets.get_font(0));
}

TEST(AssetholderOverwrite, overwritetexture) {
	asset_holder test_assets;
	test_assets.add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::SPRING, "Images/spring.png");
	test_assets.add_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::SPRING, "Images/teleporter.png");
	EXPECT_NO_CRASH(test_assets.get_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::SPRING));
}

TEST(AssetholderOverwrite, overwritesoundbuffer) {
	asset_holder test_assets;
	test_assets.add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD, "Sounds/button_forward.flac");
	test_assets.add_sound_buffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD, "Sounds/button_backward.flac");
	EXPECT_NO_CRASH(test_assets.get_soundbuffer(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD));
}

TEST(AssetholderInvalidAddress,InvalidFontFile) {
	asset_holder test_assets;
	EXPECT_NO_CRASH(test_assets.add_font(0, "Invalid_font.otf"));
}

TEST(AssetholderInvalidAddress, InvalidTextureFile) {
	asset_holder test_assets;
	EXPECT_NO_CRASH(test_assets.add_texture(asset_holder::group_member_name::OJJAS, 0,"Invalid_texture.png"));
}

TEST(AssetholderInvalidAddress, InvalidSoundbufferFile) {
	asset_holder test_assets;
	EXPECT_NO_CRASH(test_assets.add_sound_buffer(asset_holder::group_member_name::OJJAS, 0, "Invalid_soundbuffer.wav"));
}