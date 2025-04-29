-- migrate:up
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Create companies table
CREATE TABLE companies (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    name VARCHAR(255) NOT NULL,
    tax_id VARCHAR(50) UNIQUE,
    parent_id UUID REFERENCES companies(id),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

-- Add an index for better performance when querying by parent
CREATE INDEX idx_companies_parent_id ON companies(parent_id);

-- migrate:down
DROP INDEX IF EXISTS idx_companies_parent_id;
DROP TABLE IF EXISTS companies;
DROP EXTENSION IF EXISTS "uuid-ossp"; 