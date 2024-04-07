#ifndef MYSQL_FUNCTIONS_H
#define MYSQL_FUNCTIONS_H

#include <iostream>
#include <mariadb/mysql.h>

struct connection_details
{
    const char *server, *user, *password, *database;
};

// Function to set up MySQL connection
MYSQL* mysql_connection_setup(struct connection_details mysql_details) {
    MYSQL *connection = mysql_init(NULL); 

    // Connect to the database
    if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)) {
        std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1); 
    }

    return connection;
}

// Function to execute a query and return the result
MYSQL_RES* mysql_perform_query(MYSQL *connection, const char *sql_query) {
    if (mysql_query(connection, sql_query)) {
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        return nullptr;
    }

    return mysql_use_result(connection);
}

// Function to insert a new user into the database
bool insert_user(MYSQL *connection, const char *username, const char *email, int age, const char *gender, const char *join_date) {
    char query[200];
    snprintf(query, sizeof(query), "INSERT INTO tblUsers (Username, Email, Age, Gender, JoinDate) VALUES('%s', '%s', %d, '%s', '%s')", username, email, age, gender, join_date);

    if (mysql_query(connection, query)) {
        std::cout << "Insert Error: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}

// Function to retrieve all users from the database
MYSQL_RES* get_all_users(MYSQL *connection) {
    return mysql_perform_query(connection, "SELECT * FROM tblUsers");
}

// Function to update user information in the database
bool update_user(MYSQL *connection, int user_id, const char *username, const char *email, int age, const char *gender) {
    char query[200];
    snprintf(query, sizeof(query), "UPDATE tblUsers SET Username='%s', Email='%s', Age=%d, Gender='%s' WHERE UserID=%d", username, email, age, gender, user_id);

    if (mysql_query(connection, query)) {
        std::cout << "Update Error: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}

// Function to delete a user from the database
bool delete_user(MYSQL *connection, int user_id) {
    char query[100];
    snprintf(query, sizeof(query), "DELETE FROM tblUsers WHERE UserID=%d", user_id);

    if (mysql_query(connection, query)) {
        std::cout << "Delete Error: " << mysql_error(connection) << std::endl;
        return false;
    }

    return true;
}

#endif // MYSQL_FUNCTIONS_H
