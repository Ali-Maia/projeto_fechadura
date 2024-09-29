import sqlite3

# Conecta ao banco de dados
conn = sqlite3.connect('tags.db')
cursor = conn.cursor()

# Função para adicionar uma nova tag ao banco de dados
def adicionar_tag(nova_tag):
    try:
        # Insere uma nova tag na tabela 'tags'
        cursor.execute("INSERT INTO tags (id) VALUES (?)", (nova_tag,))
        conn.commit()  # Confirma as alterações no banco de dados
        print(f"Tag {nova_tag} adicionada com sucesso!")
    except sqlite3.IntegrityError:
        print("Erro: A tag já existe no banco de dados.")
    except Exception as e:
        print(f"Erro ao adicionar a tag: {e}")

# Exemplo de como adicionar uma nova tag
nova_tag = "12345678"  # Substitua pelo UID da nova tag
adicionar_tag(nova_tag)

# Fecha a conexão com o banco de dados
conn.close()
