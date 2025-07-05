<script>
// Dashboard logic can be added here
const companies = [
  { name: "Acme Corporation", entityType: "Corp" },
  { name: "Smith Family LLC", entityType: "LLC" },
  { name: "Johnson & Partners", entityType: "Joint Taxpayer" },
  { name: "Tech Solutions Inc", entityType: "Corp" },
  { name: "Green Energy LLC", entityType: "LLC" },
  { name: "Williams Consulting", entityType: "Joint Taxpayer" }
];
</script>

<section class="dashboard">
  <h1>Financial Health Dashboard</h1>
  <div class="summary-cards">
    <div class="card">
      <div class="card-title">ARR</div>
      <div class="card-value">212K</div>
      Annual Recurring Revenue.
    </div>
    <div class="card">
      <div class="card-title">Gross Margin</div>
      <div class="card-value">59%</div>
      Gross Profit / Revenue
    </div>
    <div class="card">
      <div class="card-title">Working Capital</div>
      <div class="card-value">341K</div>
      Current Assets - Current Liabilities
    </div>
  </div>
  <div class="summary-cards">
    <div class="card">
      <div class="card-title">EBITDA</div>
      <div class="card-value">274K</div>
      Earnings before interest, taxes, depreciation
    </div>
    <div class="card">
      <div class="card-title">NET Margin</div>
      <div class="card-value">17%</div>

    </div>
    <div class="card">
      <div class="card-title">CAC</div>
      <div class="card-value">755</div>
      Sales + Marketing / New Customers
    </div>
  </div>
  
  <div class="companies-section">
    <h2>Companies in System</h2>
    <div class="table-container">
      <table class="companies-table">
        <thead>
          <tr>
            <th>Company Name</th>
            <th>Entity Type</th>
          </tr>
        </thead>
        <tbody>
          {#each companies as company}
            <tr>
              <td>{company.name}</td>
              <td><span class="entity-badge {company.entityType.toLowerCase()}">{company.entityType}</span></td>
            </tr>
          {/each}
        </tbody>
      </table>
    </div>
  </div>

  <div class="dashboard-content">
    <div class="chart-placeholder">
      <span>Chart or Recent Activity</span>
    </div>
  </div>
</section>

<style>
.dashboard {
  width: 100%;
  max-width: 1200px;
  margin: 0 auto;
  padding: 2rem 0;
}
.dashboard h1 {
  font-size: 2rem;
  margin-bottom: 2rem;
}
.dashboard h2 {
  font-size: 1.5rem;
  margin-bottom: 1rem;
  color: #333;
}
.summary-cards {
  display: flex;
  gap: 2rem;
  margin-bottom: 2.5rem;
}
.card {
  background: #fff;
  border-radius: 10px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.06);
  padding: 1.5rem 2rem;
  min-width: 180px;
  flex: 1;
  display: flex;
  flex-direction: column;
  align-items: flex-start;
}
.card-title {
  font-size: 1.1rem;
  color: #888;
  margin-bottom: 0.5rem;
}
.card-value {
  font-size: 2rem;
  font-weight: bold;
  color: #222;
}
.companies-section {
  margin-bottom: 2.5rem;
}
.table-container {
  background: #fff;
  border-radius: 10px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.06);
  overflow: hidden;
}
.companies-table {
  width: 100%;
  border-collapse: collapse;
}
.companies-table th {
  background: #f8f9fa;
  padding: 1rem;
  text-align: left;
  font-weight: 600;
  color: #333;
  border-bottom: 1px solid #e9ecef;
}
.companies-table td {
  padding: 1rem;
  border-bottom: 1px solid #e9ecef;
}
.companies-table tr:last-child td {
  border-bottom: none;
}
.entity-badge {
  padding: 0.25rem 0.75rem;
  border-radius: 20px;
  font-size: 0.875rem;
  font-weight: 500;
}
.entity-badge.corp {
  background: #e3f2fd;
  color: #1976d2;
}
.entity-badge.llc {
  background: #f3e5f5;
  color: #7b1fa2;
}
.entity-badge.joint {
  background: #fff3e0;
  color: #f57c00;
}
.dashboard-content {
  background: #fff;
  border-radius: 10px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.06);
  padding: 2rem;
  min-height: 220px;
  display: flex;
  align-items: center;
  justify-content: center;
}
.chart-placeholder {
  color: #aaa;
  font-size: 1.2rem;
}
</style>