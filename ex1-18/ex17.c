#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int max_data;
    int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->db) {
            if (conn->db->rows) {
                for (int i = 0; i < conn->db->max_rows; i++) {
                    free(conn->db->rows[i].name);
                    free(conn->db->rows[i].email);
                }
                free(conn->db->rows);
            }
            free(conn->db);
        }
        if (conn->file) fclose(conn->file);
        free(conn);
    }
}

void die(const char *message, struct Connection *conn)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    if (conn) {
        Database_close(conn);
    }
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(&conn->db->max_data, sizeof(int), 1, conn->file);
    if (rc != 1) die("Failed to load max_data", conn);

    rc = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
    if (rc != 1) die("Failed to load max_rows", conn);

    conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
    if (!conn->db->rows) die("Memory error", conn);

    for (int i = 0; i < conn->db->max_rows; i++) {
        conn->db->rows[i].name = malloc(conn->db->max_data);
        conn->db->rows[i].email = malloc(conn->db->max_data);
        if (!conn->db->rows[i].name || !conn->db->rows[i].email)
            die("Memory error", conn);

        rc = fread(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
        if (rc != 1) die("Failed to load id", conn);
        rc = fread(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
        if (rc != 1) die("Failed to load set", conn);
        rc = fread(conn->db->rows[i].name, 1, conn->db->max_data, conn->file);
        if (rc != conn->db->max_data) die("Failed to load name", conn);
        rc = fread(conn->db->rows[i].email, 1, conn->db->max_data, conn->file);
        if (rc != conn->db->max_data) die("Failed to load email", conn);
    }
}

struct Connection *Database_open(const char *filename, char mode,
                                 int max_data, int max_rows)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error", NULL);

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory error", conn);

    conn->db->max_data = max_data;
    conn->db->max_rows = max_rows;
    conn->db->rows = NULL;

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Failed to open the file", conn);

    return conn;
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);
    if (rc != 1) die("Failed to write max_data", conn);

    rc = fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);
    if (rc != 1) die("Failed to write max_rows", conn);

    for (int i = 0; i < conn->db->max_rows; i++) {
        rc = fwrite(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
        if (rc != 1) die("Failed to write id", conn);
        rc = fwrite(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
        if (rc != 1) die("Failed to write set", conn);
        rc = fwrite(conn->db->rows[i].name, 1, conn->db->max_data, conn->file);
        if (rc != conn->db->max_data) die("Failed to write name", conn);
        rc = fwrite(conn->db->rows[i].email, 1, conn->db->max_data, conn->file);
        if (rc != conn->db->max_data) die("Failed to write email", conn);
    }

    rc = fflush(conn->file);
    if (rc == -1) die("Cannot flush database", conn);
}

void Database_create(struct Connection *conn)
{
    conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
    if (!conn->db->rows) die("Memory error", conn);

    for (int i = 0; i < conn->db->max_rows; i++) {
        struct Address addr = {.id = i, .set = 0};
        addr.name = calloc(conn->db->max_data, 1);
        addr.email = calloc(conn->db->max_data, 1);
        if (!addr.name || !addr.email) die("Memory error", conn);
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id,
                  const char *name, const char *email)
{
    if (id < 0 || id >= conn->db->max_rows)
        die("Invalid id", conn);

    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;

    strncpy(addr->name, name, conn->db->max_data - 1);
    addr->name[conn->db->max_data - 1] = '\0';

    strncpy(addr->email, email, conn->db->max_data - 1);
    addr->email[conn->db->max_data - 1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
    if (id < 0 || id >= conn->db->max_rows)
        die("Invalid id", conn);

    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    if (id < 0 || id >= conn->db->max_rows)
        die("Invalid id", conn);

    struct Address addr = {.id = id, .set = 0};
    addr.name = calloc(conn->db->max_data, 1);
    addr.email = calloc(conn->db->max_data, 1);
    if (!addr.name || !addr.email) die("Memory error", conn);

    free(conn->db->rows[id].name);
    free(conn->db->rows[id].email);
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    for (int i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &conn->db->rows[i];
        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 5)
        die("USAGE: ex17 <MAX_DATA> <MAX_ROWS> <dbfile> <action> [params]", NULL);

    int max_data = atoi(argv[1]);
    int max_rows = atoi(argv[2]);
    char *filename = argv[3];
    char action = argv[4][0];

    if (max_data <= 0 || max_rows <= 0)
        die("max_data and max_rows must be positive", NULL);

    struct Connection *conn = Database_open(filename, action, max_data, max_rows);
    int id = 0;

    if (argc > 5) id = atoi(argv[5]);

    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 6) die("Need an id to get", conn);
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 7) die("Need id, name, email to set", conn);
            Database_set(conn, id, argv[5], argv[6]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 6) die("Need id to delete", conn);
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);
    return 0;
}