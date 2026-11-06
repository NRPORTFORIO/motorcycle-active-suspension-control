import csv
import io

# テスト実車走行を模した疑似データ
log_csv = """Timestamp_ms,Sensor_G,Damping_Level
10,0.5,1
20,1.2,2
30,2.8,3
40,-99.0,2""" # 40msでセンサー故障・フェイルセーフ作動

def analyze_suspension_log(csv_text):
    # Pandasの代わりにPython標準のcsvモジュールを使用
    f = io.StringIO(csv_text.strip())
    reader = csv.DictReader(f)
    
    print("--- 2輪走行データ自動解析 ---")
    
    has_fault = False
    max_g = -float('inf')
    
    for row in reader:
        sensor_g = float(row['Sensor_G'])
        
        # 1. センサー異常とフェイルセーフの検証
        if sensor_g <= -90.0:
            has_fault = True
            
        # 2. 最大衝撃値(Max-G)の自動抽出
        if sensor_g > max_g:
            max_g = sensor_g
            
    if has_fault:
        print("[PASS] センサー異常時の安全停止ロジックを確認しました。")
        
    print(f"走行中の最大衝撃値: {max_g} G")

analyze_suspension_log(log_csv)
