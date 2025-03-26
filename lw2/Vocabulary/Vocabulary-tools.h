#pragma once

void ToLower(std::string& s);
bool IsMainVocabularyPhrase(const std::string& phrase);
void SavePhraseInVocabularies(const std::string& phrase, const std::string& translation, Vocabulary& main, Vocabulary& opposite);
std::ifstream OpenFileForReading(const std::string& fileName);
std::ofstream OpenFileForWriting(const std::string& fileName);
void AskUserToSaveVocabulary(std::string fileName, const FullVocabulary& v);
