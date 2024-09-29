import sqlite3

conn = sqlite3.connect('tags.db')
cursor = conn.cursor()

cursor.execute('''
CREATE TABLE IF NOT EXISTS tags (
    id TEXT PRIMARY KEY
)
''')

# Adiciona algumas tags para teste
cursor.execute("INSERT INTO tags (id) VALUES ('219C251D')")
cursor.execute("INSERT INTO tags (id) VALUES ('87654321')")
conn.commit()

conn.close()
