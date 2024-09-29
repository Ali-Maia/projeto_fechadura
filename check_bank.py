import serial
import sqlite3

# Configuração da porta serial
ser = serial.Serial('COM3', 9600)  # Substitua 'COM3' pela porta correta no seu sistema
conn = sqlite3.connect('tags.db')  # Conexão ao banco de dados SQLite
cursor = conn.cursor()

def verificar_tag(tag):
    cursor.execute("SELECT * FROM tags WHERE id = ?", (tag,))
    result = cursor.fetchone()
    if result:
        return True
    else:
        return False

while True:
    if ser.in_waiting > 0:
        uid = ser.readline().decode('utf-8').strip()
        print(f"Tag lida: {uid}")

        if verificar_tag(uid):
            print("Tag encontrada no banco de dados!")
            ser.write(b'1')
        else:
            print("Tag NÃO encontrada no banco de dados!")
            ser.write(b'0')

conn.close()
