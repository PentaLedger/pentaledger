FROM golang:1.24-alpine3.21 AS builder

WORKDIR /app

# Install build tools
RUN apk add --no-cache git

# Copy Go module files and download dependencies first (caching optimization)
#COPY go.mod go.sum ./
#RUN go mod download

COPY . .

RUN go build -o ./bin/pentaledger-api ./cmd/api

FROM alpine:3.19

WORKDIR /app

COPY --from=builder /app/bin/pentaledger-api .

EXPOSE 4000

CMD ["./pentaledger-api"]
