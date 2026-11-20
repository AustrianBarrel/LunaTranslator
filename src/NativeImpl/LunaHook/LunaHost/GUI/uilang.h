#pragma once

// UI language support for the standalone LunaHost GUI.
// The shared InfoStrings module only carries the host/hook strings (in Chinese,
// translated at runtime through Host's i18n query callback), so the GUI keeps
// its own UI string table and language list here.

enum UILANG
{
    Chinese,
    TradChinese,
    English,
    Russian,
};

extern UILANG curr_lang;
extern std::vector<std::tuple<UILANG, std::wstring, std::vector<std::string>>> lang_map;

const char *map_from_support_lang(UILANG);
UILANG map_to_support_lang(const char *);

// Host::I18NQueryCallback: translates a raw (Chinese) host/hook string into curr_lang
// using the lang/*.json files embedded as resources.
std::optional<std::wstring> ui_i18n_query(const std::wstring &raw);
