-- migrate:up
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

-- migrate:down
DROP INDEX IF EXISTS idx_gambling_log_location_id;
DROP INDEX IF EXISTS idx_gambling_log_date;
DROP TABLE IF EXISTS gambling_log; 