<script>
  import { auth } from '$lib/auth';
  import RoleGuard from '$lib/RoleGuard.svelte';

  let selectedReport = 'pl';
  let dateRange = 'ytd'; // ytd, qtd, mtd, custom
  let startDate = '';
  let endDate = '';
  let showDatePicker = false;

  // Sample P&L data
  const plData = {
    revenue: {
      sales: 1250000,
      services: 450000,
      other: 75000
    },
    costOfGoods: {
      materials: 650000,
      labor: 280000,
      overhead: 120000
    },
    operatingExpenses: {
      salaries: 320000,
      rent: 48000,
      utilities: 18000,
      marketing: 45000,
      insurance: 12000,
      depreciation: 25000,
      other: 15000
    },
    otherIncome: {
      interest: 8000,
      investments: 12000
    },
    otherExpenses: {
      interest: 15000,
      taxes: 85000
    }
  };

  // Calculate totals
  $: totalRevenue = Object.values(plData.revenue).reduce((sum, val) => sum + val, 0);
  $: totalCOGS = Object.values(plData.costOfGoods).reduce((sum, val) => sum + val, 0);
  $: totalOperatingExpenses = Object.values(plData.operatingExpenses).reduce((sum, val) => sum + val, 0);
  $: totalOtherIncome = Object.values(plData.otherIncome).reduce((sum, val) => sum + val, 0);
  $: totalOtherExpenses = Object.values(plData.otherExpenses).reduce((sum, val) => sum + val, 0);
  $: grossProfit = totalRevenue - totalCOGS;
  $: operatingIncome = grossProfit - totalOperatingExpenses;
  $: netIncome = operatingIncome + totalOtherIncome - totalOtherExpenses;

  function updateDateRange(range) {
    dateRange = range;
    if (range !== 'custom') {
      showDatePicker = false;
    } else {
      showDatePicker = true;
    }
  }

  function generateReport() {
    // In a real app, this would fetch data from the backend
    console.log('Generating report:', { selectedReport, dateRange, startDate, endDate });
    alert('Report generated successfully!');
  }

  function exportReport() {
    // In a real app, this would generate and download a PDF/Excel file
    console.log('Exporting report:', selectedReport);
    alert('Report exported successfully!');
  }

  function printReport() {
    window.print();
  }
</script>

<RoleGuard resource="reports" action="read" fallback="You need permission to access reports.">
  <section class="reports">
    <div class="reports-header">
      <h1>Reports & Analytics</h1>
      <p>Generate and view financial reports and business insights</p>
    </div>

    <div class="reports-controls">
      <div class="report-selector">
        <label for="report-type">Report Type</label>
        <select id="report-type" bind:value={selectedReport}>
          <option value="pl">Profit & Loss Statement</option>
          <option value="balance">Balance Sheet</option>
          <option value="cashflow">Cash Flow Statement</option>
          <option value="customers">Customer Analysis</option>
          <option value="vendors">Vendor Analysis</option>
        </select>
      </div>

      <div class="date-controls">
        <label>Date Range</label>
        <div class="date-buttons">
          <button 
            class={dateRange === 'ytd' ? 'active' : ''} 
            on:click={() => updateDateRange('ytd')}
          >
            YTD
          </button>
          <button 
            class={dateRange === 'qtd' ? 'active' : ''} 
            on:click={() => updateDateRange('qtd')}
          >
            QTD
          </button>
          <button 
            class={dateRange === 'mtd' ? 'active' : ''} 
            on:click={() => updateDateRange('mtd')}
          >
            MTD
          </button>
          <button 
            class={dateRange === 'custom' ? 'active' : ''} 
            on:click={() => updateDateRange('custom')}
          >
            Custom
          </button>
        </div>
      </div>

      {#if showDatePicker}
        <div class="custom-dates">
          <div class="date-input">
            <label for="start-date">Start Date</label>
            <input type="date" id="start-date" bind:value={startDate} />
          </div>
          <div class="date-input">
            <label for="end-date">End Date</label>
            <input type="date" id="end-date" bind:value={endDate} />
          </div>
        </div>
      {/if}

      <div class="report-actions">
        <button class="generate-btn" on:click={generateReport}>Generate Report</button>
        <button class="export-btn" on:click={exportReport}>Export</button>
        <button class="print-btn" on:click={printReport}>Print</button>
      </div>
    </div>

    {#if selectedReport === 'pl'}
      <div class="pl-report">
        <div class="report-header">
          <h2>Profit & Loss Statement</h2>
          <div class="report-meta">
            <span>Period: {dateRange.toUpperCase()}</span>
            <span>Generated: {new Date().toLocaleDateString()}</span>
          </div>
        </div>

        <div class="pl-sections">
          <!-- Revenue Section -->
          <div class="pl-section revenue">
            <h3>Revenue</h3>
            <div class="pl-items">
              <div class="pl-item">
                <span>Sales Revenue</span>
                <span class="amount">${plData.revenue.sales.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Service Revenue</span>
                <span class="amount">${plData.revenue.services.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Other Revenue</span>
                <span class="amount">${plData.revenue.other.toLocaleString()}</span>
              </div>
              <div class="pl-item total">
                <span>Total Revenue</span>
                <span class="amount">${totalRevenue.toLocaleString()}</span>
              </div>
            </div>
          </div>

          <!-- Cost of Goods Sold -->
          <div class="pl-section cogs">
            <h3>Cost of Goods Sold</h3>
            <div class="pl-items">
              <div class="pl-item">
                <span>Materials</span>
                <span class="amount">${plData.costOfGoods.materials.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Direct Labor</span>
                <span class="amount">${plData.costOfGoods.labor.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Overhead</span>
                <span class="amount">${plData.costOfGoods.overhead.toLocaleString()}</span>
              </div>
              <div class="pl-item total">
                <span>Total COGS</span>
                <span class="amount">${totalCOGS.toLocaleString()}</span>
              </div>
            </div>
          </div>

          <!-- Gross Profit -->
          <div class="pl-section gross-profit">
            <div class="pl-item total">
              <span>Gross Profit</span>
              <span class="amount positive">${grossProfit.toLocaleString()}</span>
            </div>
          </div>

          <!-- Operating Expenses -->
          <div class="pl-section expenses">
            <h3>Operating Expenses</h3>
            <div class="pl-items">
              <div class="pl-item">
                <span>Salaries & Wages</span>
                <span class="amount">${plData.operatingExpenses.salaries.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Rent</span>
                <span class="amount">${plData.operatingExpenses.rent.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Utilities</span>
                <span class="amount">${plData.operatingExpenses.utilities.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Marketing</span>
                <span class="amount">${plData.operatingExpenses.marketing.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Insurance</span>
                <span class="amount">${plData.operatingExpenses.insurance.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Depreciation</span>
                <span class="amount">${plData.operatingExpenses.depreciation.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Other Expenses</span>
                <span class="amount">${plData.operatingExpenses.other.toLocaleString()}</span>
              </div>
              <div class="pl-item total">
                <span>Total Operating Expenses</span>
                <span class="amount">${totalOperatingExpenses.toLocaleString()}</span>
              </div>
            </div>
          </div>

          <!-- Operating Income -->
          <div class="pl-section operating-income">
            <div class="pl-item total">
              <span>Operating Income</span>
              <span class="amount positive">${operatingIncome.toLocaleString()}</span>
            </div>
          </div>

          <!-- Other Income & Expenses -->
          <div class="pl-section other">
            <h3>Other Income & Expenses</h3>
            <div class="pl-items">
              <div class="pl-item">
                <span>Interest Income</span>
                <span class="amount positive">${plData.otherIncome.interest.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Investment Income</span>
                <span class="amount positive">${plData.otherIncome.investments.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Interest Expense</span>
                <span class="amount">${plData.otherExpenses.interest.toLocaleString()}</span>
              </div>
              <div class="pl-item">
                <span>Income Taxes</span>
                <span class="amount">${plData.otherExpenses.taxes.toLocaleString()}</span>
              </div>
            </div>
          </div>

          <!-- Net Income -->
          <div class="pl-section net-income">
            <div class="pl-item total">
              <span>Net Income</span>
              <span class="amount positive">${netIncome.toLocaleString()}</span>
            </div>
          </div>
        </div>

        <div class="pl-summary">
          <div class="summary-item">
            <span>Gross Profit Margin</span>
            <span class="percentage">{(grossProfit / totalRevenue * 100).toFixed(1)}%</span>
          </div>
          <div class="summary-item">
            <span>Operating Margin</span>
            <span class="percentage">{(operatingIncome / totalRevenue * 100).toFixed(1)}%</span>
          </div>
          <div class="summary-item">
            <span>Net Profit Margin</span>
            <span class="percentage">{(netIncome / totalRevenue * 100).toFixed(1)}%</span>
          </div>
        </div>
      </div>
    {:else}
      <div class="other-reports">
        <div class="placeholder">
          <h3>{selectedReport === 'balance' ? 'Balance Sheet' : 
               selectedReport === 'cashflow' ? 'Cash Flow Statement' :
               selectedReport === 'customers' ? 'Customer Analysis' :
               'Vendor Analysis'} Report</h3>
          <p>This report type is coming soon. Currently showing Profit & Loss data.</p>
        </div>
      </div>
    {/if}
  </section>
</RoleGuard>

<style>
  .reports {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .reports-header {
    text-align: center;
    margin-bottom: 2rem;
  }

  .reports-header h1 {
    font-size: 2rem;
    margin-bottom: 0.5rem;
    color: #333;
  }

  .reports-header p {
    color: #666;
    font-size: 1.1rem;
  }

  .reports-controls {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
    margin-bottom: 2rem;
    display: grid;
    grid-template-columns: 1fr 1fr auto;
    gap: 1.5rem;
    align-items: end;
  }

  .report-selector,
  .date-controls {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }

  .report-selector label,
  .date-controls label {
    font-weight: 500;
    color: #333;
  }

  .report-selector select {
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
  }

  .date-buttons {
    display: flex;
    gap: 0.5rem;
  }

  .date-buttons button {
    padding: 0.5rem 1rem;
    border: 1px solid #ddd;
    background: white;
    border-radius: 4px;
    cursor: pointer;
    transition: all 0.2s;
  }

  .date-buttons button.active {
    background: #667eea;
    color: white;
    border-color: #667eea;
  }

  .date-buttons button:hover:not(.active) {
    background: #f8f9fa;
  }

  .custom-dates {
    display: flex;
    gap: 1rem;
  }

  .date-input {
    display: flex;
    flex-direction: column;
    gap: 0.25rem;
  }

  .date-input label {
    font-size: 0.875rem;
    color: #666;
  }

  .date-input input {
    padding: 0.5rem;
    border: 1px solid #ddd;
    border-radius: 4px;
  }

  .report-actions {
    display: flex;
    gap: 1rem;
  }

  .generate-btn,
  .export-btn,
  .print-btn {
    padding: 0.75rem 1.5rem;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .generate-btn {
    background: #28a745;
    color: white;
  }

  .generate-btn:hover {
    background: #218838;
  }

  .export-btn {
    background: #17a2b8;
    color: white;
  }

  .export-btn:hover {
    background: #138496;
  }

  .print-btn {
    background: #6c757d;
    color: white;
  }

  .print-btn:hover {
    background: #545b62;
  }

  .pl-report {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    overflow: hidden;
  }

  .report-header {
    padding: 1.5rem;
    background: #f8f9fa;
    border-bottom: 1px solid #e9ecef;
  }

  .report-header h2 {
    margin: 0 0 0.5rem 0;
    color: #333;
  }

  .report-meta {
    display: flex;
    gap: 2rem;
    color: #666;
    font-size: 0.9rem;
  }

  .pl-sections {
    padding: 1.5rem;
  }

  .pl-section {
    margin-bottom: 2rem;
  }

  .pl-section:last-child {
    margin-bottom: 0;
  }

  .pl-section h3 {
    margin: 0 0 1rem 0;
    color: #333;
    font-size: 1.1rem;
  }

  .pl-items {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }

  .pl-item {
    display: flex;
    justify-content: space-between;
    padding: 0.75rem;
    border-radius: 4px;
    transition: background-color 0.2s;
  }

  .pl-item:hover {
    background: #f8f9fa;
  }

  .pl-item.total {
    font-weight: 600;
    background: #f8f9fa;
    border-top: 2px solid #e9ecef;
  }

  .amount {
    font-family: 'Courier New', monospace;
    font-weight: 500;
  }

  .amount.positive {
    color: #28a745;
  }

  .gross-profit,
  .operating-income,
  .net-income {
    border-top: 2px solid #e9ecef;
    padding-top: 1rem;
  }

  .net-income {
    border-top: 3px solid #333;
  }

  .pl-summary {
    background: #f8f9fa;
    padding: 1.5rem;
    border-top: 1px solid #e9ecef;
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
  }

  .summary-item {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 1rem;
    background: white;
    border-radius: 6px;
    box-shadow: 0 1px 3px rgba(0,0,0,0.1);
  }

  .summary-item span:first-child {
    font-weight: 500;
    color: #333;
  }

  .percentage {
    font-weight: 600;
    color: #28a745;
    font-size: 1.1rem;
  }

  .other-reports {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 3rem;
    text-align: center;
  }

  .placeholder h3 {
    color: #333;
    margin-bottom: 1rem;
  }

  .placeholder p {
    color: #666;
  }

  @media (max-width: 768px) {
    .reports-controls {
      grid-template-columns: 1fr;
      gap: 1rem;
    }

    .date-buttons {
      flex-wrap: wrap;
    }

    .custom-dates {
      flex-direction: column;
    }

    .report-actions {
      flex-direction: column;
    }

    .report-meta {
      flex-direction: column;
      gap: 0.5rem;
    }

    .pl-summary {
      grid-template-columns: 1fr;
    }
  }

  @media print {
    .reports-controls,
    .report-actions {
      display: none;
    }
  }
</style> 