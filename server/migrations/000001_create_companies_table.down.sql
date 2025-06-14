-- Drop triggers
DROP TRIGGER IF EXISTS set_updated_at ON companies;
DROP FUNCTION IF EXISTS update_updated_at_column;

-- Drop child tables first due to foreign key dependencies
DROP TABLE IF EXISTS company_tax_accounts;
DROP TABLE IF EXISTS company_notes;
DROP TABLE IF EXISTS company_registrations;
DROP TABLE IF EXISTS company_documents;
DROP TABLE IF EXISTS company_contacts;
DROP TABLE IF EXISTS company_addresses;

-- Drop parent table last
DROP TABLE IF EXISTS companies;

-- Drop index (safe if not already dropped with tables)
DROP INDEX IF EXISTS idx_companies_parent_id;
DROP INDEX IF EXISTS idx_company_addresses_company_id;
DROP INDEX IF EXISTS idx_company_contacts_company_id;
DROP INDEX IF EXISTS idx_company_documents_company_id;
DROP INDEX IF EXISTS idx_company_registrations_company_id;

-- Drop custom enum types
DROP TYPE IF EXISTS entity_type_enum;

-- Drop extensions (optional, might be used by other migrations)
-- Only drop if you're sure it's safe:
-- DROP EXTENSION IF EXISTS "uuid-ossp";
