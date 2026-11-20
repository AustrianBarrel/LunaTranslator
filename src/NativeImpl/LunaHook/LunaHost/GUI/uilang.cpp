#include "uilang.h"
#include <nlohmann/json.hpp>

UILANG curr_lang = English;

std::vector<std::tuple<UILANG, std::wstring, std::vector<std::string>>> lang_map = {
    {Chinese, L"简体中文", {"zh"}},
    {TradChinese, L"繁體中文", {"cht", "zh-TW"}},
    {English, L"English", {"en"}},
    {Russian, L"Русский язык", {"ru"}},
};

const char *map_from_support_lang(UILANG _c)
{
    for (auto &&[c, _, ls] : lang_map)
    {
        if (c == _c)
            return ls[0].c_str();
    }
    return "en";
}

UILANG map_to_support_lang(const char *s)
{
    for (auto &&[c, _, ls] : lang_map)
        for (auto &&l : ls)
            if (l == s)
                return c;

    std::string sub = s;
    auto _fnd = sub.find('-');
    if (_fnd != sub.npos)
    {
        sub = sub.substr(0, _fnd);
        for (auto &&[c, _, ls] : lang_map)
            for (auto &&l : ls)
                if (l == sub)
                    return c;
    }
    return English;
}

std::unordered_map<LANG_STRINGS_UI, std::unordered_map<UILANG, const wchar_t *>>
    _internal_lang_strings_ui = {
        {WndSelectProcess, {
                               {English, L"SelectProcess"},
                               {Chinese, L"选择进程"},
                               {TradChinese, L"選擇處理程序"},
                               {Russian, L"Выбор процесса"},
                           }},
        {WndLunaHostGui, {
                             {English, L"LunaTranslator Hook Simple GUI"},
                         }},
        {TSetting, {
                       {English, L"Settings"},
                       {Chinese, L"设置"},
                       {TradChinese, L"設定"},
                       {Russian, L"Настройки"},
                   }},
        {TPlugins, {
                       {English, L"Plugins"},
                       {Chinese, L"插件"},
                       {TradChinese, L"外掛程式"},
                       {Russian, L"Плагины"},
                   }},
        {NotifyInvalidHookCode, {
                                    {English, L"Invalid HookCode"},
                                    {Chinese, L"特殊码无效"},
                                    {TradChinese, L"特殊碼無效"},
                                    {Russian, L"Неверный код хука"},
                                }},
        {BtnDetach, {
                        {English, L"Detach"},
                        {Chinese, L"从游戏分离"},
                        {TradChinese, L"從遊戲分離"},
                        {Russian, L"Отключить"},
                    }},
        {BtnSaveHook, {
                          {English, L"Save hook"},
                          {Chinese, L"保存钩子"},
                          {TradChinese, L"儲存勾點"},
                          {Russian, L"Сохранить хук"},
                      }},
        {BtnAttach, {
                        {English, L"Attach"},
                        {Chinese, L"注入进程"},
                        {TradChinese, L"注入處理程序"},
                        {Russian, L"Подключить"},
                    }},
        {BtnRefresh, {
                         {English, L"Refresh"},
                         {Chinese, L"刷新"},
                         {TradChinese, L"重新整理"},
                         {Russian, L"Обновить"},
                     }},
        {BtnToClipboard, {
                             {English, L"Copy To Clipboard"},
                             {Chinese, L"复制到剪贴板"},
                             {TradChinese, L"複製到剪貼簿"},
                             {Russian, L"Скопировать в буфер обмена"},
                         }},
        {BtnReadOnly, {
                          {English, L"Text box Read only"},
                          {Chinese, L"文本框只读"},
                          {TradChinese, L"文字框唯讀"},
                          {Russian, L"Текстовое поле доступно только для чтения"},
                      }},
        {BtnInsertUserHook, {
                                {English, L"Insert UserHook"},
                                {Chinese, L"插入特殊码"},
                                {TradChinese, L"插入特殊碼"},
                                {Russian, L"Добавить польз. хук"},
                            }},
        {LblFlushDelay, {
                            {English, L"Flush delay"},
                            {Chinese, L"刷新延迟"},
                            {TradChinese, L"排清延遲"},
                            {Russian, L"Задержка сброса"},
                        }},
        {LblFilterRepeat, {
                              {English, L"Filter repetition"},
                              {Chinese, L"过滤重复文本"},
                              {TradChinese, L"過濾重複文字"},
                              {Russian, L"Фильтр повторов"},
                          }},
        {LblLanguage, {
                          {English, L"Language"},
                          {Chinese, L"语言"},
                          {TradChinese, L"語言"},
                          {Russian, L"Язык"},
                      }},
        {LblCodePage, {
                          {English, L"Default codepage"},
                          {Chinese, L"默认代码页"},
                          {TradChinese, L"預設字碼頁"},
                          {Russian, L"Кодовая страница по умолчанию"},
                      }},
        {LblMaxBuff, {
                         {English, L"Max buffer size"},
                         {Chinese, L"最大缓冲区长度"},
                         {TradChinese, L"最大緩衝區長度"},
                         {Russian, L"Максимальный размер буфера"},
                     }},
        {LblMaxHist, {
                         {English, L"Max history size"},
                         {Chinese, L"最大缓存文本长度"},
                         {TradChinese, L"最大快取文字長度"},
                         {Russian, L"Максимальный размер истории"},
                     }},
        {LblAutoAttach, {
                            {English, L"Auto attach"},
                            {Chinese, L"自动附加"},
                            {TradChinese, L"自動附加"},
                            {Russian, L"Автоподключение"},
                        }},
        {LblAutoAttach_savedonly, {
                                      {English, L"Auto attach (saved only)"},
                                      {Chinese, L"自动附加 (仅限保存过配置的游戏)"},
                                      {TradChinese, L"自動附加（僅限儲存過配置的遊戲）"},
                                      {Russian, L"Автоподключение (только сохраненные)"},
                                  }},
        {MenuCopyHookCode, {
                               {English, L"CopyHookCode"},
                               {Chinese, L"复制特殊码"},
                               {TradChinese, L"複製特殊碼"},
                               {Russian, L"Скопировать код хука"},
                           }},
        {MenuRemoveHook, {
                             {English, L"RemoveHook"},
                             {Chinese, L"移除钩子"},
                             {TradChinese, L"移除勾點"},
                             {Russian, L"Удалить хук"},
                         }},
        {MenuDetachProcess, {
                                {English, L"DetachProcess"},
                                {Chinese, L"离开进程"},
                                {TradChinese, L"離開處理程序"},
                                {Russian, L"Отключиться от процесса"},
                            }},
        {MenuRemeberSelect, {
                                {English, L"Remeber Hook Selection"},
                                {Chinese, L"记住选择的钩子"},
                                {TradChinese, L"記住選擇的勾點"},
                                {Russian, L"Запомнить выбранный хук"},
                            }},
        {MenuForgetSelect, {
                               {English, L"Forget Hook Selection"},
                               {Chinese, L"忘掉选择的钩子"},
                               {TradChinese, L"忘掉選擇的勾點"},
                               {Russian, L"Забыть выбранный хук"},
                           }},
        {MenuAddPlugin, {
                            {English, L"Add Plugin"},
                            {Chinese, L"添加插件"},
                            {TradChinese, L"新增外掛程式"},
                            {Russian, L"Добавить плагин"},
                        }},
        {MenuRemovePlugin, {
                               {English, L"Remove Plugin"},
                               {Chinese, L"移除插件"},
                               {TradChinese, L"移除外掛程式"},
                               {Russian, L"Удалить плагин"},
                           }},
        {MenuPluginRankUp, {
                               {English, L"Up"},
                               {Chinese, L"上移"},
                               {TradChinese, L"上移"},
                               {Russian, L"Вверх"},
                           }},
        {MenuPluginRankDown, {
                                 {English, L"Down"},
                                 {Chinese, L"下移"},
                                 {TradChinese, L"下移"},
                                 {Russian, L"Вниз"},
                             }},
        {MenuPluginEnable, {
                               {English, L"Enable"},
                               {Chinese, L"使用"},
                               {TradChinese, L"使用"},
                               {Russian, L"Включить"},
                           }},
        {MenuPluginVisSetting, {
                                   {English, L"Show Setting"},
                                   {Chinese, L"显示设置"},
                                   {TradChinese, L"顯示設定"},
                                   {Russian, L"Показать настройки"},
                               }},
        {DefaultFont, {
                          {English, L"Arial"},
                          {Chinese, L"微软雅黑"},
                          {TradChinese, L"Microsoft JhengHei"},
                          {Russian, L"Arial"},
                      }},
        {InvalidPlugin, {
                            {English, L"Invalid Plugin!"},
                            {Chinese, L"插件无效！"},
                            {TradChinese, L"外掛程式無效！"},
                            {Russian, L"Неверный плагин!"},
                        }},
        {InvalidDll, {
                         {English, L"Invalid Dll!"},
                         {Chinese, L"Dll无效！"},
                         {TradChinese, L"DLL 無效！"},
                         {Russian, L"Неверная DLL!"},
                     }},
        {InvalidDump, {
                          {English, L"Dumplicated!"},
                          {Chinese, L"重复！"},
                          {TradChinese, L"重複！"},
                          {Russian, L"Дубликат!"},
                      }},
        {MsgError, {
                       {English, L"Error"},
                       {Chinese, L"错误"},
                       {TradChinese, L"錯誤"},
                       {Russian, L"Ошибка"},
                   }},
        {BtnOk, {
                    {English, L"OK"},
                    {Chinese, L"确定"},
                    {TradChinese, L"確定"},
                    {Russian, L"OK"},
                }},
        {HS_TEXT, {
                      {English, L"Text"},
                      {Chinese, L"文本"},
                      {TradChinese, L"文字"},
                      {Russian, L"Текст"},
                  }},
        {VersionLatest, {
                            {English, L"Latest version"},
                            {Chinese, L"最新版本"},
                            {TradChinese, L"最新版本"},
                            {Russian, L"Последняя версия"},
                        }},
        {VersionCurrent, {
                             {English, L"Current version"},
                             {Chinese, L"当前版本"},
                             {TradChinese, L"目前版本"},
                             {Russian, L"Текущая версия"},
                         }},
        {LIST_HOOK, {
                        {English, L"Hook"},
                    }},
        {COPYSELECTION, {
                            {English, L"auto send selected text in textbox to clipboard"},
                            {Chinese, L"自动将文本框中选取的文本复制到剪贴板"},
                            {TradChinese, L"自動將文字框中選取的文字複製到剪貼簿"},
                            {Russian, L"Автоматически копировать выделенный текст в буфер обмена"},
                        }},
        {FONTSELECT, {
                         {English, L"Select Font"},
                         {Chinese, L"选择字体"},
                         {TradChinese, L"選擇字型"},
                         {Russian, L"Выбрать шрифт"},
                     }},
};

const wchar_t *langhelper::operator[](LANG_STRINGS_UI langstring)
{
    auto found = _internal_lang_strings_ui.find(langstring);
    if (found == _internal_lang_strings_ui.end())
        return L"";
    auto &&_ = found->second;
    auto &&__ = _.find(curr_lang);
    if (__ == _.end())
        __ = _.find(English);
    if (__ == _.end())
        return L"";
    return __->second;
}

// Resource names must match the RCDATA entries written by GUI/CMakeLists.txt.
static const wchar_t *lang_resource_name(UILANG lang)
{
    switch (lang)
    {
    case English:
        return L"LANG_EN";
    case TradChinese:
        return L"LANG_CHT";
    case Russian:
        return L"LANG_RU";
    default:
        return nullptr;
    }
}

static const nlohmann::json *load_lang_json(UILANG lang)
{
    static std::mutex lock;
    static std::map<UILANG, nlohmann::json> cache;
    std::lock_guard _(lock);
    if (auto found = cache.find(lang); found != cache.end())
        return &found->second;

    auto &j = cache[lang];
    if (auto name = lang_resource_name(lang))
    {
        if (HRSRC res = FindResourceW(NULL, name, RT_RCDATA))
        {
            if (HGLOBAL data = LoadResource(NULL, res))
            {
                auto begin = (const char *)LockResource(data);
                auto size = SizeofResource(NULL, res);
                if (begin && size)
                    j = nlohmann::json::parse(begin, begin + size, nullptr, false);
            }
        }
    }
    return &j;
}

std::optional<std::wstring> ui_i18n_query(const std::wstring &raw)
{
    // The raw strings are Chinese already.
    if (curr_lang == Chinese)
        return {};
    auto j = load_lang_json(curr_lang);
    if (!j->is_object())
        return {};
    auto found = j->find(WideStringToString(raw));
    if (found == j->end() || !found->is_string())
        return {};
    return StringToWideString(found->get<std::string>());
}
