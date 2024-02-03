#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

typedef MYSQL Connection;

Connection *initializeConnection(const char *host, const char *user, const char *password, const char *dbname)
{
    MYSQL *connection = mysql_init(NULL);

    if (connection == NULL)
    {
        fprintf(stderr, "Flha ao inicializar a conexão com o Mysql");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(connection, host, user, password, dbname, 0, NULL, 0))
    {
        fprintf(stderr, "%s %s %s %s", host, user, password, dbname);
        fprintf(stderr, "Erro ao conectar ao MySQL: %s\n", mysql_error(connection));
        mysql_close(connection);
        exit(EXIT_FAILURE);
    }

    return connection;
}

void closeConnection(Connection *conn)
{
    mysql_close(conn);
}

int main()
{
    // Definir o número máximo de conexões no seu pool
    const int maxConnections = 10;
    Connection *connections[maxConnections];

    const char *host = "localhost";
    const char *user = "root";
    const char *password = "password";
    const char *dbname = "banco_teste";
    bool error = false;

    // Inicializar as conexões
        for (int i = 0; i < maxConnections; i++)
        {
            connections[i] = initializeConnection(host, user, password, dbname);

            // Consulta SQL para obter informações sobre as conexões ativas

            const char *insertQuery = "INSERT INTO teste (nome, idade) VALUES ('Exemplo', 25);";
            for (int j = 0; j < 100; j++)
            {
                error = mysql_query(connections[i], insertQuery) != 0;
            }

            if (error)
            {
                fprintf(stderr, "Erro ao executar a consulta de inserção: %s\n", mysql_error(connections[i]));
                mysql_close(connections[i]);
                exit(EXIT_FAILURE);
            }
        }

        while(1) {
            
        }

    // // Realizar operações

    // // Liberar os recursos das conexões quando não forem mais utilizadas
    // for (int i = 0; i < maxConnections; i++)
    // {
    //     closeConnection(&connections[i]);
    // }
}