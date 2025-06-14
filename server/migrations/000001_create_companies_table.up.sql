--CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Optional: Create ENUM for entity_type
CREATE TYPE entity_type_enum AS ENUM ('LLC', 'C-Corp', 'S-Corp', 'Nonprofit', 'Partnership', 'Sole Proprietor');

CREATE TABLE companies (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    legal_name VARCHAR(255) NOT NULL,
    display_name VARCHAR(255),
    entity_type entity_type_enum NOT NULL,
    tax_id VARCHAR(50) UNIQUE,
    state_of_incorporation VARCHAR(2),
    formation_date DATE,
    dissolved_date DATE,
    status VARCHAR(50) DEFAULT 'Active',
    parent_id UUID REFERENCES companies(id) ON DELETE SET NULL,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    created_by UUID,
    updated_by UUID
);

CREATE INDEX idx_companies_parent_id ON companies(parent_id);

-- Trigger to auto-update updated_at
CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = NOW();
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER set_updated_at
BEFORE UPDATE ON companies
FOR EACH ROW
EXECUTE FUNCTION update_updated_at_column();

CREATE TABLE company_addresses (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    company_id UUID NOT NULL REFERENCES companies(id) ON DELETE CASCADE,
    address_type VARCHAR(50) NOT NULL,  -- e.g., 'registered', 'mailing', 'principal'
    street VARCHAR(255),
    street2 VARCHAR(255),
    city VARCHAR(100),
    state VARCHAR(2),
    postal_code VARCHAR(20),
    country VARCHAR(2) DEFAULT 'US',
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_company_addresses_company_id ON company_addresses(company_id);

CREATE TABLE company_contacts (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    company_id UUID NOT NULL REFERENCES companies(id) ON DELETE CASCADE,
    contact_type VARCHAR(50),  -- e.g., 'registered agent', 'executive', 'support'
    name VARCHAR(255) NOT NULL,
    title VARCHAR(100),
    email VARCHAR(255),
    phone VARCHAR(50),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_company_contacts_company_id ON company_contacts(company_id);

CREATE TABLE company_documents (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    company_id UUID NOT NULL REFERENCES companies(id) ON DELETE CASCADE,
    document_type VARCHAR(100) NOT NULL,  -- e.g., 'articles of incorporation', 'minutes'
    file_path TEXT NOT NULL,              -- Or use bytea if storing files in DB
    uploaded_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    description TEXT
);

CREATE INDEX idx_company_documents_company_id ON company_documents(company_id);

CREATE TABLE company_registrations (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    company_id UUID NOT NULL REFERENCES companies(id) ON DELETE CASCADE,
    jurisdiction VARCHAR(100),  -- e.g., 'Delaware', 'Minnesota'
    registration_number VARCHAR(100),
    registration_date DATE,
    status VARCHAR(50),         -- e.g., 'active', 'expired'
    renewal_date DATE
);

CREATE INDEX idx_company_registrations_company_id ON company_registrations(company_id);

CREATE TABLE company_notes (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    company_id UUID NOT NULL REFERENCES companies(id) ON DELETE CASCADE,
    note TEXT NOT NULL,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    created_by UUID
);

CREATE TABLE company_tax_accounts (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    company_id UUID NOT NULL REFERENCES companies(id) ON DELETE CASCADE,
    tax_account_type VARCHAR(50), -- e.g., 'EIN', 'State Sales Tax'
    account_number VARCHAR(100),
    jurisdiction VARCHAR(100),
    registered_date DATE
);
