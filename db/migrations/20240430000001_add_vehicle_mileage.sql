-- migrate:up
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

-- Create vehicles table
CREATE TABLE vehicles (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    make VARCHAR(100) NOT NULL,
    model VARCHAR(100) NOT NULL,
    year INTEGER NOT NULL,
    vin VARCHAR(17) UNIQUE,
    license_plate VARCHAR(20),
    company_id UUID REFERENCES companies(id),
    is_active BOOLEAN DEFAULT true,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

-- Create trips table
CREATE TABLE trips (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    vehicle_id UUID REFERENCES vehicles(id) ON DELETE CASCADE,
    driver_id UUID REFERENCES companies(id),  -- Assuming drivers are companies/employees
    start_odometer DECIMAL(10, 2) NOT NULL,
    end_odometer DECIMAL(10, 2) NOT NULL,
    start_time TIMESTAMP WITH TIME ZONE NOT NULL,
    end_time TIMESTAMP WITH TIME ZONE NOT NULL,
    purpose TEXT,
    start_location_id UUID REFERENCES addresses(id),
    end_location_id UUID REFERENCES addresses(id),
    is_business_use BOOLEAN DEFAULT false,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT valid_odometer CHECK (end_odometer >= start_odometer),
    CONSTRAINT valid_times CHECK (end_time >= start_time)
);

-- Create trip_expenses table for tracking expenses related to trips
CREATE TABLE trip_expenses (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    trip_id UUID REFERENCES trips(id) ON DELETE CASCADE,
    expense_type VARCHAR(50) NOT NULL,  -- fuel, toll, parking, etc.
    amount DECIMAL(10, 2) NOT NULL,
    currency VARCHAR(3) DEFAULT 'USD',
    receipt_url TEXT,
    notes TEXT,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

-- Create indexes
CREATE INDEX idx_vehicles_company_id ON vehicles(company_id);
CREATE INDEX idx_vehicles_vin ON vehicles(vin);
CREATE INDEX idx_vehicles_license_plate ON vehicles(license_plate);
CREATE INDEX idx_trips_vehicle_id ON trips(vehicle_id);
CREATE INDEX idx_trips_driver_id ON trips(driver_id);
CREATE INDEX idx_trips_start_time ON trips(start_time);
CREATE INDEX idx_trips_end_time ON trips(end_time);
CREATE INDEX idx_trip_expenses_trip_id ON trip_expenses(trip_id);

-- Create function to update updated_at timestamp
CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

-- Create triggers for updated_at
CREATE TRIGGER update_vehicles_updated_at
    BEFORE UPDATE ON vehicles
    FOR EACH ROW
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_trips_updated_at
    BEFORE UPDATE ON trips
    FOR EACH ROW
    EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_trip_expenses_updated_at
    BEFORE UPDATE ON trip_expenses
    FOR EACH ROW
    EXECUTE FUNCTION update_updated_at_column();

-- migrate:down
DROP TRIGGER IF EXISTS update_trip_expenses_updated_at ON trip_expenses;
DROP TRIGGER IF EXISTS update_trips_updated_at ON trips;
DROP TRIGGER IF EXISTS update_vehicles_updated_at ON vehicles;
DROP FUNCTION IF EXISTS update_updated_at_column();
DROP INDEX IF EXISTS idx_trip_expenses_trip_id;
DROP INDEX IF EXISTS idx_trips_end_time;
DROP INDEX IF EXISTS idx_trips_start_time;
DROP INDEX IF EXISTS idx_trips_driver_id;
DROP INDEX IF EXISTS idx_trips_vehicle_id;
DROP INDEX IF EXISTS idx_vehicles_license_plate;
DROP INDEX IF EXISTS idx_vehicles_vin;
DROP INDEX IF EXISTS idx_vehicles_company_id;
DROP TABLE IF EXISTS trip_expenses;
DROP TABLE IF EXISTS trips;
DROP TABLE IF EXISTS vehicles;
DROP EXTENSION IF EXISTS "uuid-ossp"; 