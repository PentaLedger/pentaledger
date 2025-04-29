# Database Migrations

This directory contains database migrations managed by [dbmate](https://github.com/amacneil/dbmate).

## Setup

1. Install dbmate:
   ```bash
   # macOS
   brew install dbmate

   # Linux
   curl -fsSL -o /usr/local/bin/dbmate https://github.com/amacneil/dbmate/releases/latest/download/dbmate-linux-amd64
   chmod +x /usr/local/bin/dbmate

   # Windows (using scoop)
   scoop install dbmate
   ```

2. Create a `.env` file in the project root with the following content:
   ```bash
   DATABASE_URL="postgres://postgres:postgres@localhost:5432/pentaledger?sslmode=disable"
   DBMATE_MIGRATIONS_DIR="db/migrations"
   DBMATE_SCHEMA_FILE="db/schema.sql"
   DBMATE_SEEDS_DIR="db/seeds"
   ```

3. Create the database:
   ```bash
   dbmate create
   ```

## Usage

### Creating a new migration
```bash
dbmate new create_users_table
```

### Running migrations
```bash
# Run all pending migrations
dbmate up

# Rollback the last migration
dbmate down

# Show migration status
dbmate status
```

### Working with the database
```bash
# Open a psql console
dbmate psql

# Dump the current schema
dbmate dump

# Load the schema
dbmate load
```

## Migration Files

Migration files are stored in `db/migrations/` and follow the naming convention:
`YYYYMMDDHHMMSS_description.sql`

Example migration file:
```sql
-- migrate:up
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    email VARCHAR(255) NOT NULL UNIQUE,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

-- migrate:down
DROP TABLE users;
```

## Seeds

Seed files are stored in `db/seeds/` and can be run using:
```bash
dbmate seed
``` 