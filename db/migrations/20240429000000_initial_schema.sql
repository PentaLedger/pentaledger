-- migrate:up
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Create addresses table (reusable for both billing and shipping addresses)
CREATE TABLE addresses (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    line1 VARCHAR(255) NOT NULL,
    line2 VARCHAR(255),
    city VARCHAR(100) NOT NULL,
    postal_code VARCHAR(20) NOT NULL,
    country_subdivision_code VARCHAR(10) NOT NULL,
    country VARCHAR(100) NOT NULL DEFAULT 'United States',
    latitude DECIMAL(10, 7),
    longitude DECIMAL(10, 7),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);
CREATE INDEX idx_addresses_postal_code ON addresses(postal_code);

-- Create companies table
CREATE TABLE companies (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    name VARCHAR(255) NOT NULL,
    tax_id VARCHAR(50) UNIQUE,
    parent_id UUID REFERENCES companies(id),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);
CREATE INDEX idx_companies_parent_id ON companies(parent_id);

CREATE TABLE gambling_log (
    id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    date DATE NOT NULL,
    establishment_name VARCHAR(255) NOT NULL,
    establishment_address TEXT NOT NULL,
    time_of_day TIME NOT NULL,
    wagering_type VARCHAR(100) NOT NULL,
    location_id VARCHAR(50) NOT NULL,
    w2_winnings DECIMAL(12,2) NOT NULL DEFAULT 0,
    winnings DECIMAL(12,2) NOT NULL DEFAULT 0,
    losses DECIMAL(12,2) NOT NULL DEFAULT 0,
    notes TEXT,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

-- Create index on date for faster date-based queries
CREATE INDEX idx_gambling_log_date ON gambling_log(date);

-- Create index on location_id for faster location-based queries
CREATE INDEX idx_gambling_log_location_id ON gambling_log(location_id);


-- Create function to update updated_at timestamp
CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

-- Create triggers for updated_at
CREATE TRIGGER update_addresses_updated_at
    BEFORE UPDATE ON addresses
    FOR EACH ROW
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_companies_updated_at
    BEFORE UPDATE ON companies
    FOR EACH ROW
    EXECUTE FUNCTION update_updated_at_column();

-- migrate:down

DROP TRIGGER IF EXISTS update_addresses_updated_at ON addresses;
DROP TRIGGER IF EXISTS update_companies_updated_at ON companies;
DROP FUNCTION IF EXISTS update_updated_at_column();

DROP INDEX IF EXISTS idx_companies_parent_id;
DROP TABLE IF EXISTS companies;
DROP TABLE IF EXISTS addresses;

DROP INDEX IF EXISTS idx_addresses_postal_code;
DROP INDEX IF EXISTS idx_companies_parent_id;

DROP INDEX IF EXISTS idx_gambling_log_location_id;
DROP INDEX IF EXISTS idx_gambling_log_date;
DROP TABLE IF EXISTS gambling_log; 

DROP EXTENSION IF EXISTS "uuid-ossp"; 