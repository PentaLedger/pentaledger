-- Create ENUM type for party_subtype
DO $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_type WHERE typname = 'party_subtype') THEN
        CREATE TYPE party_subtype AS ENUM ('organization', 'person');
    END IF;
END
$$;

-- party table
CREATE TABLE IF NOT EXISTS party (
    id UUID PRIMARY KEY,
    party_subtype party_subtype NOT NULL
);

-- party_type table
CREATE TABLE IF NOT EXISTS party_type (
    id VARCHAR(255) PRIMARY KEY,
    description VARCHAR(255)
);

-- party_classification table
CREATE TABLE IF NOT EXISTS party_classification (
    party_id UUID NOT NULL,
    party_type_id VARCHAR(255) NOT NULL DEFAULT '',
    from_date DATE NOT NULL DEFAULT '1000-01-01',
    thru_date DATE NOT NULL DEFAULT '9999-12-31',
    PRIMARY KEY (party_id, party_type_id, from_date),
    FOREIGN KEY (party_id) REFERENCES party(id),
    FOREIGN KEY (party_type_id) REFERENCES party_type(id)
);

-- organization table
CREATE TABLE IF NOT EXISTS organization (
    id UUID PRIMARY KEY,
    name VARCHAR(255) NOT NULL DEFAULT '',
    FOREIGN KEY (id) REFERENCES party(id)
);

-- person table
CREATE TABLE IF NOT EXISTS person (
    id UUID PRIMARY KEY,
    name VARCHAR(255) NOT NULL DEFAULT '',
    FOREIGN KEY (id) REFERENCES party(id)
);

