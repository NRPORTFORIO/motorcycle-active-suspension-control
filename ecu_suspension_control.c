include <stdio.h>
#include <stdbool.h>

// サスペンションステータス
typedef struct {
    float sensor_g;
    int damping_level;       // 1:ソフト / 2:ミディアム / 3:ハード
    bool is_fail_safe_active;
} SuspensionEcu;

// 減衰力自動調整ロジック（AstemoのEERA想定）
void adjust_damping(SuspensionEcu *ecu, float raw_g_input) {
    if (raw_g_input <= -90.0f) { // センサー異常検知
        ecu->is_fail_safe_active = true;
        ecu->damping_level = 2; // 安全モード
        return;
    }
    // Gフォースに応じた制御
    if (raw_g_input >= 2.5f)      ecu->damping_level = 3; // ハード
    else if (raw_g_input >= 1.0f) ecu->damping_level = 2; // ミディアム
    else                          ecu->damping_level = 1; // ソフト
}
