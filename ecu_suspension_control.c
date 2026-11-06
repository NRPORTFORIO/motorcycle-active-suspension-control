#include <stdio.h>
#include <stdbool.h>
// 1. 最初に構造体を定義する
typedef struct {
    float sensor_g;
    int damping_level; // 1:ソフト / 2:ミディアム / 3:ハード
    bool is_fail_safe_active;
} SuspensionEcu;

// 2. 次に関数を定義する
void adjust_damping(SuspensionEcu *ecu, float raw_g_input) {
    if (raw_g_input <= -90.0f) { // センサー異常検知
        ecu->is_fail_safe_active = true;
        ecu->damping_level = 2; // 安全モード
        return;
    }

    // Gフォースに応じた制御
    if (raw_g_input >= 2.5f) ecu->damping_level = 3; // ハード
    else if (raw_g_input >= 1.0f) ecu->damping_level = 2; // ミディアム
    else ecu->damping_level = 1; // ソフト
}

// 3. 最後に main 関数を定義する（上で定義した型や関数をここで使う）
int main(void) {
    SuspensionEcu my_ecu = {0.0f, 1, false};

    // 正常時：ソフトモードのテスト (G = 0.5f)
    adjust_damping(&my_ecu, 0.5f);
    printf("G: 0.5 -> Damping Level: %d, FailSafe: %s\n", 
           my_ecu.damping_level, my_ecu.is_fail_safe_active ? "ON" : "OFF");

    // 正常時：ハードモードのテスト (G = 2.8f)
    adjust_damping(&my_ecu, 2.8f);
    printf("G: 2.8 -> Damping Level: %d, FailSafe: %s\n", 
           my_ecu.damping_level, my_ecu.is_fail_safe_active ? "ON" : "OFF");

    // 異常発生時：フェイルセーフのテスト (G = -95.0f)
    adjust_damping(&my_ecu, -95.0f);
    printf("G:-95.0 -> Damping Level: %d, FailSafe: %s\n", 
           my_ecu.damping_level, my_ecu.is_fail_safe_active ? "ON" : "OFF");

    return 0;
}
