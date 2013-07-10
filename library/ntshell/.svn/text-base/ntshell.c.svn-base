/**
 * @file ntshell.c
 * @author Shinichiro Nakamura
 * @brief 小規模組み込みシステム向けのシェルシステムの実装。
 */

/*
 * ===============================================================
 *  Natural Tiny Shell (NT-Shell)
 *  Version 0.0.6
 * ===============================================================
 * Copyright (c) 2010-2011 Shinichiro Nakamura
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * ===============================================================
 */

#include "ntshell.h"
#include "ntlibc.h"

#define VERSION_MAJOR 0     /**< メジャー番号。 */
#define VERSION_MINOR 0     /**< マイナー番号。 */
#define VERSION_RELEASE 6   /**< リリース番号。 */

/**
 * @brief 処理で用いるデータ構造体。
 *
 * @details
 * vtparseはユーザデータのポインタを設定することができる。
 * Natural Tiny Shellはこれを使って自身の処理で必要な情報を保持する。
 */
typedef struct {
    text_editor_t *editor;
    text_history_t *history;
    int suggest_index;
    char suggest_source[TEXTEDITOR_MAXLEN];
    int (*func_read)(char *buf, int cnt);
    int (*func_write)(const char *buf, int cnt);
    int (*func_cb)(const char *text);
} ntshell_user_data_t;

#define SUGGEST_INDEX(vtp) \
    ((ntshell_user_data_t *)(vtp)->user_data)->suggest_index
#define SUGGEST_SOURCE(vtp) \
    ((ntshell_user_data_t *)(vtp)->user_data)->suggest_source

/**
 * @brief テキストエディタを取得する。
 *
 * @param vtp vtparse構造体。
 */
#define GET_EDITOR(vtp) \
    ((ntshell_user_data_t *)(vtp)->user_data)->editor

/**
 * @brief テキストヒストリを取得する。
 *
 * @param vtp vtparse構造体。
 */
#define GET_HISTORY(vtp) \
    ((ntshell_user_data_t *)(vtp)->user_data)->history

/**
 * @brief シリアルポートから読み込む。
 *
 * @param vtp vtparse構造体。
 * @param buf 読み込みバッファ。
 * @param cnt 読み込み文字数。
 */
#define SERIAL_READ(vtp,buf,cnt) \
    ((ntshell_user_data_t *)(vtp)->user_data)->func_read(buf, cnt)

/**
 * @brief シリアルポートへ書き込む。
 *
 * @param vtp vtparse構造体。
 * @param buf 書き込みバッファ。
 * @param cnt 書き込み文字数。
 */
#define SERIAL_WRITE(vtp,buf,cnt) \
    ((ntshell_user_data_t *)(vtp)->user_data)->func_write(buf, cnt)

/**
 * @brief コールバックを呼び出す。
 *
 * @param vtp vtparse構造体。
 * @param text コールバック関数へ渡す文字列。
 */
#define CALLBACK(vtp, text) \
    ((ntshell_user_data_t *)(vtp)->user_data)->func_cb(text)

/**
 * @brief テキストヒストリで１つ後ろを辿る。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_history_prev(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    if (text_history_read_point_prev(GET_HISTORY(parser))) {
        char txt[TEXTHISTORY_MAXLEN];
        int n = text_history_read(GET_HISTORY(parser), &txt[0], sizeof(txt));
        if (0 < n) {
            SERIAL_WRITE(parser, "\x1b[2K", 4);
            SERIAL_WRITE(parser, "\x1b[80D", 5);
            SERIAL_WRITE(parser, ">", 1);
            SERIAL_WRITE(parser, txt, n);
            text_editor_set_text(GET_EDITOR(parser), txt);
        }
    }
}

/**
 * @brief テキストヒストリで１つ前を辿る。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_history_next(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    if (text_history_read_point_next(GET_HISTORY(parser))) {
        char txt[TEXTHISTORY_MAXLEN];
        int n = text_history_read(GET_HISTORY(parser), &txt[0], sizeof(txt));
        if (0 < n) {
            SERIAL_WRITE(parser, "\x1b[2K", 4);
            SERIAL_WRITE(parser, "\x1b[80D", 5);
            SERIAL_WRITE(parser, ">", 1);
            SERIAL_WRITE(parser, txt, n);
            text_editor_set_text(GET_EDITOR(parser), txt);
        }
    }
}

/**
 * @brief カーソルを左へ移動させる。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_cursor_left(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    if (text_editor_cursor_left(GET_EDITOR(parser))) {
        SERIAL_WRITE(parser, "\x1b[1D", 4);
    }
}

/**
 * @brief カーソルを右へ移動させる。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_cursor_right(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    if (text_editor_cursor_right(GET_EDITOR(parser))) {
        SERIAL_WRITE(parser, "\x1b[1C", 4);
    }
}

/**
 * @brief エンターキーの処理を実行する。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_enter(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    char txt[TEXTEDITOR_MAXLEN];
    text_editor_get_text(GET_EDITOR(parser), &txt[0], sizeof(txt));
    text_editor_clear(GET_EDITOR(parser));
    text_history_write(GET_HISTORY(parser), txt);
    SERIAL_WRITE(parser, "\r\n", 2);
    CALLBACK(parser, txt);
    SERIAL_WRITE(parser, ">", 1);
}

/**
 * @brief キャンセルキーの処理を実行する。
 * @details
 * 一般的なOSのCTRL+C処理はシグナルを発行し、受信したプロセスが
 * 中断処理を実行する。
 * ここでのキャンセルは見た目を再現したもので、
 * 入力中の文字列を破棄してカーソルを新しい入力に備えて復帰させるものだ。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_cancel(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    SERIAL_WRITE(parser, "^C\r\n", 4);
    text_editor_clear(GET_EDITOR(parser));
    SERIAL_WRITE(parser, ">", 1);
}

/**
 * @brief 挿入処理を実行する。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_insert(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {

    /*
     * 入力があった場合、入力補完状態から抜ける。
     */
    SUGGEST_INDEX(parser) = -1;

    /*
     * テキストエディタを使って文字を文字列に挿入する。
     */
    if (text_editor_insert(GET_EDITOR(parser), ch)) {
        char txt[TEXTEDITOR_MAXLEN];
        int len = text_editor_get_text(GET_EDITOR(parser), &txt[0], sizeof(txt));
        int pos = text_editor_cursor_get_position(GET_EDITOR(parser));
        SERIAL_WRITE(parser, (char *)&ch, sizeof(ch));
        int n = len - pos;
        if (n > 0) {
            int i;
            SERIAL_WRITE(parser, txt + pos, len - pos);
            for (i = 0; i < n; i++) {
                SERIAL_WRITE(parser, "\x1b[1D", 4);
            }
        }
    }
}

/**
 * @brief バックスペース処理を実行する。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_backspace(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    if (text_editor_backspace(GET_EDITOR(parser))) {
        char txt[TEXTEDITOR_MAXLEN];
        SERIAL_WRITE(parser, "\x1b[1D", 4);
        int len = text_editor_get_text(GET_EDITOR(parser), &txt[0], sizeof(txt));
        int pos = text_editor_cursor_get_position(GET_EDITOR(parser));
        int n = len - pos;
        if (n > 0) {
            int i;
            SERIAL_WRITE(parser, txt + pos, len - pos);
            SERIAL_WRITE(parser, " ", 1);
            for (i = 0; i < n + 1; i++) {
                SERIAL_WRITE(parser, "\x1b[1D", 4);
            }
        } else {
            SERIAL_WRITE(parser, " ", 1);
            SERIAL_WRITE(parser, "\x1b[1D", 4);
        }
    }
}

/**
 * @brief 入力補完処理を実行する。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch 入力文字。
 */
static void actfunc_suggest(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    char buf[TEXTEDITOR_MAXLEN];
    if (SUGGEST_INDEX(parser) < 0) {
        /*
         * 入力補完モードにこれから入る場合。
         * 現在の入力文字列を元に補完候補を取得する。
         */
        if (text_editor_get_text(
                    GET_EDITOR(parser),
                    SUGGEST_SOURCE(parser),
                    sizeof(SUGGEST_SOURCE(parser))) > 0) {
            SUGGEST_INDEX(parser) = 0;
            if (text_history_find(
                        GET_HISTORY(parser),
                        SUGGEST_INDEX(parser),
                        SUGGEST_SOURCE(parser),
                        buf,
                        sizeof(buf)) == 0) {
                // 候補が見つかればテキストを設定して、インデックスをメモする。
                int n = ntlibc_strlen((const char *)buf);
                SERIAL_WRITE(parser, "\x1b[2K", 4);
                SERIAL_WRITE(parser, "\x1b[80D", 5);
                SERIAL_WRITE(parser, ">", 1);
                SERIAL_WRITE(parser, buf, n);
                text_editor_set_text(GET_EDITOR(parser), buf);
            } else {
                // 候補がなければ入力補完モードから抜ける。
                SUGGEST_INDEX(parser) = -1;
            }
        }
    } else {
        /*
         * 既に入力補完モードに入っている場合、
         * 次の候補を探して見つかればテキストとして設定する。
         */
        SUGGEST_INDEX(parser) = SUGGEST_INDEX(parser) + 1;
        if (text_history_find(
                    GET_HISTORY(parser),
                    SUGGEST_INDEX(parser),
                    SUGGEST_SOURCE(parser),
                    buf,
                    sizeof(buf)) == 0) {
            // 候補が見つかればテキストを設定する。
            int n = ntlibc_strlen((const char *)buf);
            SERIAL_WRITE(parser, "\x1b[2K", 4);
            SERIAL_WRITE(parser, "\x1b[80D", 5);
            SERIAL_WRITE(parser, ">", 1);
            SERIAL_WRITE(parser, buf, n);
            text_editor_set_text(GET_EDITOR(parser), buf);
        } else {
            // 候補が見つからなければ元の入力文字列に戻し、入力補完モードから抜ける。
            int n = ntlibc_strlen(SUGGEST_SOURCE(parser));
            SERIAL_WRITE(parser, "\x1b[2K", 4);
            SERIAL_WRITE(parser, "\x1b[80D", 5);
            SERIAL_WRITE(parser, ">", 1);
            SERIAL_WRITE(parser, SUGGEST_SOURCE(parser), n);
            text_editor_set_text(GET_EDITOR(parser), SUGGEST_SOURCE(parser));
            SUGGEST_INDEX(parser) = -1;
        }
    }
}

static void actfunc_cursor_head(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    SERIAL_WRITE(parser, "\x1b[80D", 5);
    SERIAL_WRITE(parser, ">", 1);
    text_editor_cursor_head(GET_EDITOR(parser));
}

static void actfunc_cursor_tail(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    char buf[TEXTEDITOR_MAXLEN];
    int len;
    text_editor_get_text(GET_EDITOR(parser), buf, sizeof(buf));
    len = ntlibc_strlen((const char *)buf);
    SERIAL_WRITE(parser, "\x1b[80D", 5);
    SERIAL_WRITE(parser, ">", 1);
    SERIAL_WRITE(parser, buf, len);
    text_editor_cursor_tail(GET_EDITOR(parser));
}

/**
 * @brief アクションテーブルのデータ構造体。
 * @details
 * アクションは状態と入力文字によって与えられる。
 * アクションに対する関数もここで定義する。
 */
typedef struct {
    vtparse_action_t action;
    unsigned char ch;
    void (*func)(
            vtparse_t *parser,
            vtparse_action_t action,
            unsigned char ch);
} ntshell_action_table_t;

/**
 * @brief アクションに対する処理関数テーブル。
 * @details
 * やってくるコードは仮想端末側の処理に依存する。
 * よって様々なプラットフォームの様々な仮想端末で試すと良い。
 *
 * <table>
 *   <th>
 *     <td>Platform</td>
 *     <td>Tools</td>
 *   </th>
 *   <tr>
 *     <td>Windows</td>
 *     <td>Hyper Terminal, Poderossa, TeraTerm</td>
 *   </tr>
 *   <tr>
 *     <td>Linux</td>
 *     <td>minicom, screen, kermit</td>
 *   </tr>
 * </table>
 */
static const ntshell_action_table_t action_table[] = {
    {VTPARSE_ACTION_EXECUTE, 0x01, actfunc_cursor_head},
    {VTPARSE_ACTION_EXECUTE, 0x02, actfunc_cursor_left},
    {VTPARSE_ACTION_EXECUTE, 0x03, actfunc_cancel},
    {VTPARSE_ACTION_EXECUTE, 0x05, actfunc_cursor_tail},
    {VTPARSE_ACTION_EXECUTE, 0x06, actfunc_cursor_right},
    {VTPARSE_ACTION_EXECUTE, 0x08, actfunc_backspace},
    {VTPARSE_ACTION_EXECUTE, 0x09, actfunc_suggest},
    {VTPARSE_ACTION_EXECUTE, 0x0d, actfunc_enter},
    {VTPARSE_ACTION_EXECUTE, 0x0e, actfunc_history_next},
    {VTPARSE_ACTION_EXECUTE, 0x10, actfunc_history_prev},
    {VTPARSE_ACTION_CSI_DISPATCH, 0x41, actfunc_history_prev},
    {VTPARSE_ACTION_CSI_DISPATCH, 0x42, actfunc_history_next},
    {VTPARSE_ACTION_CSI_DISPATCH, 0x43, actfunc_cursor_right},
    {VTPARSE_ACTION_CSI_DISPATCH, 0x44, actfunc_cursor_left},
    {VTPARSE_ACTION_PRINT, 0x7f, actfunc_backspace},
};

/**
 * @brief パーサーに対するコールバック関数。
 * @details vtparseモジュールのコールバック関数に従った実装である。
 *
 * @param parser パーサー。
 * @param action アクション。
 * @param ch キャラクタ。
 */
void parser_callback(
        vtparse_t *parser,
        vtparse_action_t action,
        unsigned char ch) {
    ntshell_action_table_t *p;
    int i;
    const int ACTTBLSIZ = sizeof(action_table) / sizeof(action_table[0]);

    /*
     * 制御コードに対する処理はテーブルから探す。
     */
    p = (ntshell_action_table_t *)action_table;
    for (i = 0; i < ACTTBLSIZ; i++) {
        if ((p->action == action) && (p->ch == ch)) {
            p->func(parser, action, ch);
            return;
        }
        p++;
    }

    /*
     * 通常の文字列は入力として扱う。
     */
    if (VTPARSE_ACTION_PRINT == action) {
        actfunc_insert(parser, action, ch);
    }
}

/**
 * @brief Natural Tiny Shellのバージョンを返す。
 * @details 返すバージョンはリリースバージョンである。
 *
 * @param major メージャーバージョン。
 * @param minor マイナーバージョン。
 * @param release リリースバージョン。
 */
void ntshell_version(int *major, int *minor, int *release)
{
    *major = VERSION_MAJOR;
    *minor = VERSION_MINOR;
    *release = VERSION_RELEASE;
}

/**
 * @brief Natural Tiny Shellを実行する。
 * @details この関数は実行を返さない。
 *
 * @param parser VT100パーサー。
 * @param editor テキストエディタ。
 * @param history テキストヒストリ。
 * @param func_read シリアルリード関数。
 * @param func_write シリアルライト関数。
 * @param func_cb コールバック関数。
 */
void ntshell_execute(
        ntshell_t *p,
        int (*func_read)(char *buf, int cnt),
        int (*func_write)(const char *buf, int cnt),
        int (*func_cb)(const char *text))
{
    /*
     * vtparseはユーザデータへのポインタを設定できるようになっている。
     * Natural Tiny Shellはこれを利用してテキストエディタやヒストリ、
     * リード関数やライト関数、コールバック関数を処理の中で使用できる
     * ようにしてある。
     */
    ntshell_user_data_t user_data;

    user_data.editor = &(p->editor);
    user_data.history = &(p->history);
    user_data.func_read = func_read;
    user_data.func_write = func_write;
    user_data.func_cb = func_cb;

    p->parser.user_data = &user_data;

    /*
     * 每个模块的初始化
     */
    vtparse_init(&(p->parser), parser_callback);
    text_editor_init(GET_EDITOR(&(p->parser)));
    text_history_init(GET_HISTORY(&(p->parser)));
    SUGGEST_INDEX(&(p->parser)) = -1;

    /*
     * 用户输入的循环
     */
    SERIAL_WRITE(&(p->parser), ">", 1);
    while(1)
    {
        unsigned char ch;
        SERIAL_READ(&(p->parser), (char *)&ch, sizeof(ch));
        vtparse(&(p->parser), &ch, sizeof(ch));
    }
}

