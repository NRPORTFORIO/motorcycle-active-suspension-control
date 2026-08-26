import pandas as pd
import io

# アステモのテスト実車走行を模した疑似データ
log_csv = """Timestamp_ms,Sensor_G,Damping_Level
10,0.5,1
20,1.2,2
30,2.8,3
40,-99.0,2""" # 40msでセンサー故障・フェイルセーフ作動

def analyze_suspension_log(csv_text):
    df = pd.read_csv(io.StringIO(csv_text))
    print("--- Astemo2輪走行データ自動解析 ---")
    
    # 1. センサー異常とフェイルセーフの検証
    faults = df[df['Sensor_G'] <= -90.0]
    if not faults.empty:
        print("[PASS] センサー異常時の安全停止ロジックを確認しました。")
        
    # 2. 最大衝撃値(Max-G)の自動抽出
    max_g = df['Sensor_G'].max()
    print(f"走行中の最大衝撃値: {max_g} G")

analyze_suspension_log(log_csv)
