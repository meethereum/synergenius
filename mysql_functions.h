#ifndef MYSQL_FUNCTIONS_H
#define MYSQL_FUNCTIONS_H

#include <iostream>
#include <mariadb/mysql.h>

struct connection_details
{
    const char *server, *user, *password, *database;
};


MYSQL* mysql_connection_setup(struct connection_details mysql_details) {
    MYSQL *connection = mysql_init(NULL); 

    if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)) {
        std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1); 
    }

    return connection;
}


MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query) {
    if (mysql_query(connection, sql_query)) {
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        return nullptr;
    }

    return mysql_use_result(connection);
}


bool insert_user(MYSQL *connection, const char *username, const char *email, int age, const char *gender, const char *join_date) {
    char query[200];
    snprintf(query, sizeof(query), "INSERT INTO tblUsers (Username, Email, Age, Gender, JoinDate) VALUES('%s', '%s', %d, '%s', '%s')", username, email, age, gender, join_date);

    if (mysql_query(connection, query)) {
        std::cout << "Insert Error: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}


MYSQL_RES* get_all_users(MYSQL *connection) {
    return mysql_perform_query(connection, "SELECT * FROM tblUsers");
}


bool update_user(MYSQL *connection, int user_id, const char *username, const char *email, int age, const char *gender) {
    char query[200];
    snprintf(query, sizeof(query), "UPDATE tblUsers SET Username='%s', Email='%s', Age=%d, Gender='%s' WHERE UserID=%d", username, email, age, gender, user_id);

    if (mysql_query(connection, query)) {
        std::cout << "Update Error: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}


bool delete_user(MYSQL *connection, int user_id) {
    char query[100];
    snprintf(query, sizeof(query), "DELETE FROM tblUsers WHERE UserID=%d", user_id);

    if (mysql_query(connection, query)) {
        std::cout << "Delete Error: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}

#endif 
