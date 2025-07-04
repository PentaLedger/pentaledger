<script>
// Dashboard logic can be added here
</script>

<section class="dashboard">
  <h1>Dashboard</h1>
  <div class="summary-cards">
    <div class="card">
      <div class="card-title">Total Users</div>
      <div class="card-value">1,234</div>
    </div>
    <div class="card">
      <div class="card-title">Revenue</div>
      <div class="card-value">$12,345</div>
    </div>
    <div class="card">
      <div class="card-title">Active Sessions</div>
      <div class="card-value">87</div>
    </div>
  </div>
  <div class="summary-cards">
    <div class="card">
      <div class="card-title">Total Users</div>
      <div class="card-value">1,234</div>
    </div>
    <div class="card">
      <div class="card-title">Revenue</div>
      <div class="card-value">$12,345</div>
    </div>
    <div class="card">
      <div class="card-title">Active Sessions</div>
      <div class="card-value">87</div>
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