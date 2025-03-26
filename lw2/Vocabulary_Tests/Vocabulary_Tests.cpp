#define CATCH_CONFIG_MAIN
#include <iostream>
#include <Windows.h>
#include "../../catch2/catch.hpp"
#include "../Vocabulary/Vocabulary.h"
#include "../Vocabulary/Vocabulary-tools.h"

SCENARIO("TO LOWER")
{
	std::string en = "HeRE Is some STRiNG";
	std::string enLower = "here is some string";

	std::string ru = "СТроКА с РаЗЛИчнымИ СимВОлами, в ТОМ чИСле и Ё";
	std::string ruLower = "строка с различными символами, в том числе и ё";

	ToLower(en);
	ToLower(ru);

	REQUIRE(en == enLower);
	REQUIRE(ru == ruLower);
}

SCENARIO("ENGLISH WORDS")
{
	std::string word1 = "english";
	std::string word2 = "123127635D";
	std::string word3 = "123123F1231231";
	std::string word4 = "ENGLISH";
	REQUIRE(IsMainVocabularyPhrase(word1));
	REQUIRE(IsMainVocabularyPhrase(word2));
	REQUIRE(IsMainVocabularyPhrase(word3));
	REQUIRE(IsMainVocabularyPhrase(word4));
}

SCENARIO("RUSSIAN WORDS")
{
	std::string word1 = "русский";
	std::string word2 = "123127635Д";
	std::string word3 = "123123Ф1231231";
	std::string word4 = "Ёжик";
	REQUIRE(!IsMainVocabularyPhrase(word1));
	REQUIRE(!IsMainVocabularyPhrase(word2));
	REQUIRE(!IsMainVocabularyPhrase(word3));
	REQUIRE(!IsMainVocabularyPhrase(word4));
}

SCENARIO("ADD WORD, CHECK IF LANGUAGE IS CHECKED CORRECTLY, CHECK IF TRANSLATION IS FOUND CORRECTLY")
{
	FullVocabulary v;
	std::string en = "cat";
	std::string ru1 = "кот";
	std::string ru2 = "кошка";

	SavePhraseInVocabularies(en, ru1, v.main, v.opposite);
	SavePhraseInVocabularies(en, ru2, v.main, v.opposite);

	REQUIRE(v.main.contains(en));
	REQUIRE(v.main.find(en)->second == ru1);

	REQUIRE(v.opposite.find(ru1)->second == en);
	REQUIRE(v.opposite.find(ru2)->second == en);
}


