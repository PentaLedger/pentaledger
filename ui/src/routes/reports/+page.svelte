<script lang="ts">
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

  // Sample Balance Sheet data
  const balanceData = {
    assets: {
      current: {
        cash: 250000,
        accountsReceivable: 180000,
        inventory: 320000,
        prepaidExpenses: 15000,
        shortTermInvestments: 75000
      },
      fixed: {
        equipment: 450000,
        buildings: 1200000,
        vehicles: 180000,
        land: 800000,
        accumulatedDepreciation: -320000
      },
      other: {
        patents: 50000,
        goodwill: 75000,
        longTermInvestments: 200000
      }
    },
    liabilities: {
      current: {
        accountsPayable: 95000,
        shortTermLoans: 150000,
        accruedExpenses: 25000,
        incomeTaxesPayable: 45000,
        currentPortionLongTermDebt: 50000
      },
      longTerm: {
        longTermLoans: 800000,
        bondsPayable: 500000,
        deferredTaxes: 35000
      }
    },
    equity: {
      commonStock: 500000,
      retainedEarnings: 425000,
      additionalPaidInCapital: 75000,
      treasuryStock: -25000
    }
  };

  // Calculate P&L totals
  $: totalRevenue = Object.values(plData.revenue).reduce((sum, val) => sum + val, 0);
  $: totalCOGS = Object.values(plData.costOfGoods).reduce((sum, val) => sum + val, 0);
  $: totalOperatingExpenses = Object.values(plData.operatingExpenses).reduce((sum, val) => sum + val, 0);
  $: totalOtherIncome = Object.values(plData.otherIncome).reduce((sum, val) => sum + val, 0);
  $: totalOtherExpenses = Object.values(plData.otherExpenses).reduce((sum, val) => sum + val, 0);
  $: grossProfit = totalRevenue - totalCOGS;
  $: operatingIncome = grossProfit - totalOperatingExpenses;
  $: netIncome = operatingIncome + totalOtherIncome - totalOtherExpenses;

  // Calculate Balance Sheet totals
  $: totalCurrentAssets = Object.values(balanceData.assets.current).reduce((sum, val) => sum + val, 0);
  $: totalFixedAssets = Object.values(balanceData.assets.fixed).reduce((sum, val) => sum + val, 0);
  $: totalOtherAssets = Object.values(balanceData.assets.other).reduce((sum, val) => sum + val, 0);
  $: totalAssets = totalCurrentAssets + totalFixedAssets + totalOtherAssets;

  $: totalCurrentLiabilities = Object.values(balanceData.liabilities.current).reduce((sum, val) => sum + val, 0);
  $: totalLongTermLiabilities = Object.values(balanceData.liabilities.longTerm).reduce((sum, val) => sum + val, 0);
  $: totalLiabilities = totalCurrentLiabilities + totalLongTermLiabilities;

  $: totalEquity = Object.values(balanceData.equity).reduce((sum, val) => sum + val, 0);
  $: totalLiabilitiesAndEquity = totalLiabilities + totalEquity;

  // Financial ratios
  $: currentRatio = totalCurrentAssets / totalCurrentLiabilities;
  $: debtToEquityRatio = totalLiabilities / totalEquity;
  $: workingCapital = totalCurrentAssets - totalCurrentLiabilities;

  function updateDateRange(range: string) {
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
    {:else if selectedReport === 'balance'}
      <div class="balance-report">
        <div class="report-header">
          <h2>Balance Sheet</h2>
          <div class="report-meta">
            <span>As of: {dateRange.toUpperCase()}</span>
            <span>Generated: {new Date().toLocaleDateString()}</span>
          </div>
        </div>

        <div class="balance-sections">
          <!-- Assets -->
          <div class="balance-section assets">
            <h3>Assets</h3>
            
            <div class="balance-subsection">
              <h4>Current Assets</h4>
              <div class="balance-items">
                <div class="balance-item">
                  <span>Cash & Cash Equivalents</span>
                  <span class="amount">${balanceData.assets.current.cash.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Accounts Receivable</span>
                  <span class="amount">${balanceData.assets.current.accountsReceivable.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Inventory</span>
                  <span class="amount">${balanceData.assets.current.inventory.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Prepaid Expenses</span>
                  <span class="amount">${balanceData.assets.current.prepaidExpenses.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Short-term Investments</span>
                  <span class="amount">${balanceData.assets.current.shortTermInvestments.toLocaleString()}</span>
                </div>
                <div class="balance-item total">
                  <span>Total Current Assets</span>
                  <span class="amount">${totalCurrentAssets.toLocaleString()}</span>
                </div>
              </div>
            </div>

            <div class="balance-subsection">
              <h4>Fixed Assets</h4>
              <div class="balance-items">
                <div class="balance-item">
                  <span>Equipment</span>
                  <span class="amount">${balanceData.assets.fixed.equipment.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Buildings</span>
                  <span class="amount">${balanceData.assets.fixed.buildings.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Vehicles</span>
                  <span class="amount">${balanceData.assets.fixed.vehicles.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Land</span>
                  <span class="amount">${balanceData.assets.fixed.land.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Accumulated Depreciation</span>
                  <span class="amount negative">${balanceData.assets.fixed.accumulatedDepreciation.toLocaleString()}</span>
                </div>
                <div class="balance-item total">
                  <span>Total Fixed Assets</span>
                  <span class="amount">${totalFixedAssets.toLocaleString()}</span>
                </div>
              </div>
            </div>

            <div class="balance-subsection">
              <h4>Other Assets</h4>
              <div class="balance-items">
                <div class="balance-item">
                  <span>Patents</span>
                  <span class="amount">${balanceData.assets.other.patents.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Goodwill</span>
                  <span class="amount">${balanceData.assets.other.goodwill.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Long-term Investments</span>
                  <span class="amount">${balanceData.assets.other.longTermInvestments.toLocaleString()}</span>
                </div>
                <div class="balance-item total">
                  <span>Total Other Assets</span>
                  <span class="amount">${totalOtherAssets.toLocaleString()}</span>
                </div>
              </div>
            </div>

            <div class="balance-item total-assets">
              <span>Total Assets</span>
              <span class="amount">${totalAssets.toLocaleString()}</span>
            </div>
          </div>

          <!-- Liabilities & Equity -->
          <div class="balance-section liabilities-equity">
            <h3>Liabilities & Equity</h3>
            
            <div class="balance-subsection">
              <h4>Current Liabilities</h4>
              <div class="balance-items">
                <div class="balance-item">
                  <span>Accounts Payable</span>
                  <span class="amount">${balanceData.liabilities.current.accountsPayable.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Short-term Loans</span>
                  <span class="amount">${balanceData.liabilities.current.shortTermLoans.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Accrued Expenses</span>
                  <span class="amount">${balanceData.liabilities.current.accruedExpenses.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Income Taxes Payable</span>
                  <span class="amount">${balanceData.liabilities.current.incomeTaxesPayable.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Current Portion of Long-term Debt</span>
                  <span class="amount">${balanceData.liabilities.current.currentPortionLongTermDebt.toLocaleString()}</span>
                </div>
                <div class="balance-item total">
                  <span>Total Current Liabilities</span>
                  <span class="amount">${totalCurrentLiabilities.toLocaleString()}</span>
                </div>
              </div>
            </div>

            <div class="balance-subsection">
              <h4>Long-term Liabilities</h4>
              <div class="balance-items">
                <div class="balance-item">
                  <span>Long-term Loans</span>
                  <span class="amount">${balanceData.liabilities.longTerm.longTermLoans.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Bonds Payable</span>
                  <span class="amount">${balanceData.liabilities.longTerm.bondsPayable.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Deferred Taxes</span>
                  <span class="amount">${balanceData.liabilities.longTerm.deferredTaxes.toLocaleString()}</span>
                </div>
                <div class="balance-item total">
                  <span>Total Long-term Liabilities</span>
                  <span class="amount">${totalLongTermLiabilities.toLocaleString()}</span>
                </div>
              </div>
            </div>

            <div class="balance-item total-liabilities">
              <span>Total Liabilities</span>
              <span class="amount">${totalLiabilities.toLocaleString()}</span>
            </div>

            <div class="balance-subsection">
              <h4>Equity</h4>
              <div class="balance-items">
                <div class="balance-item">
                  <span>Common Stock</span>
                  <span class="amount">${balanceData.equity.commonStock.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Retained Earnings</span>
                  <span class="amount">${balanceData.equity.retainedEarnings.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Additional Paid-in Capital</span>
                  <span class="amount">${balanceData.equity.additionalPaidInCapital.toLocaleString()}</span>
                </div>
                <div class="balance-item">
                  <span>Treasury Stock</span>
                  <span class="amount negative">${balanceData.equity.treasuryStock.toLocaleString()}</span>
                </div>
                <div class="balance-item total">
                  <span>Total Equity</span>
                  <span class="amount">${totalEquity.toLocaleString()}</span>
                </div>
              </div>
            </div>

            <div class="balance-item total-liabilities-equity">
              <span>Total Liabilities & Equity</span>
              <span class="amount">${totalLiabilitiesAndEquity.toLocaleString()}</span>
            </div>
          </div>
        </div>

        <div class="balance-summary">
          <div class="summary-item">
            <span>Current Ratio</span>
            <span class="ratio">{currentRatio.toFixed(2)}</span>
          </div>
          <div class="summary-item">
            <span>Debt to Equity Ratio</span>
            <span class="ratio">{debtToEquityRatio.toFixed(2)}</span>
          </div>
          <div class="summary-item">
            <span>Working Capital</span>
            <span class="amount">${workingCapital.toLocaleString()}</span>
          </div>
        </div>
      </div>
    {:else}
      <div class="other-reports">
        <div class="placeholder">
          <h3>{selectedReport === 'cashflow' ? 'Cash Flow Statement' :
               selectedReport === 'customers' ? 'Customer Analysis' :
               'Vendor Analysis'} Report</h3>
          <p>This report type is coming soon. Currently showing Profit & Loss and Balance Sheet data.</p>
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

  .pl-report,
  .balance-report {
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

  .amount.negative {
    color: #dc3545;
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

  .percentage,
  .ratio {
    font-weight: 600;
    color: #28a745;
    font-size: 1.1rem;
  }

  /* Balance Sheet Styles */
  .balance-sections {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 2rem;
    padding: 1.5rem;
  }

  .balance-section h3 {
    margin: 0 0 1.5rem 0;
    color: #333;
    font-size: 1.3rem;
    padding-bottom: 0.5rem;
    border-bottom: 2px solid #e9ecef;
  }

  .balance-subsection {
    margin-bottom: 2rem;
  }

  .balance-subsection h4 {
    margin: 0 0 1rem 0;
    color: #555;
    font-size: 1rem;
    font-weight: 600;
  }

  .balance-items {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }

  .balance-item {
    display: flex;
    justify-content: space-between;
    padding: 0.75rem;
    border-radius: 4px;
    transition: background-color 0.2s;
  }

  .balance-item:hover {
    background: #f8f9fa;
  }

  .balance-item.total {
    font-weight: 600;
    background: #f8f9fa;
    border-top: 1px solid #e9ecef;
  }

  .balance-item.total-assets,
  .balance-item.total-liabilities,
  .balance-item.total-liabilities-equity {
    font-weight: 700;
    background: #e9ecef;
    border-top: 2px solid #333;
    font-size: 1.1rem;
  }

  .balance-summary {
    background: #f8f9fa;
    padding: 1.5rem;
    border-top: 1px solid #e9ecef;
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
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

    .pl-summary,
    .balance-summary {
      grid-template-columns: 1fr;
    }

    .balance-sections {
      grid-template-columns: 1fr;
      gap: 1rem;
    }
  }

  @media print {
    .reports-controls,
    .report-actions {
      display: none;
    }
  }
</style> 