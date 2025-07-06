<script lang="ts">
  import { auth } from '$lib/auth';
  import RoleGuard from '$lib/RoleGuard.svelte';

  interface Debt {
    id: number;
    name: string;
    type: 'credit-card' | 'loan';
    balance: number;
    interestRate: number;
    minimumPayment: number;
    isActive: boolean;
  }

  interface PaymentSchedule {
    month: number;
    date: string;
    totalPayment: number;
    debts: {
      debtId: number;
      debtName: string;
      payment: number;
      principal: number;
      interest: number;
      remainingBalance: number;
      isPaidOff: boolean;
    }[];
    totalPrincipal: number;
    totalInterest: number;
    totalRemainingBalance: number;
  }

  let debts: Debt[] = [
    {
      id: 1,
      name: 'Credit Card 1',
      type: 'credit-card',
      balance: 5000,
      interestRate: 18.99,
      minimumPayment: 150,
      isActive: true
    },
    {
      id: 2,
      name: 'Personal Loan',
      type: 'loan',
      balance: 8000,
      interestRate: 12.5,
      minimumPayment: 200,
      isActive: true
    },
    {
      id: 3,
      name: 'Credit Card 2',
      type: 'credit-card',
      balance: 3000,
      interestRate: 22.99,
      minimumPayment: 100,
      isActive: true
    }
  ];

  let showAddForm = false;
  let additionalMonthlyPayment = 300;
  let paymentSchedule: PaymentSchedule[] = [];
  let showSchedule = false;

  // New debt form data
  let newDebt = {
    name: '',
    type: 'credit-card' as 'credit-card' | 'loan',
    balance: 0,
    interestRate: 0,
    minimumPayment: 0
  };

  function addDebt() {
    const debt: Debt = {
      id: Math.max(...debts.map(d => d.id)) + 1,
      ...newDebt,
      isActive: true
    };
    
    debts = [...debts, debt];
    
    // Reset form
    newDebt = {
      name: '',
      type: 'credit-card',
      balance: 0,
      interestRate: 0,
      minimumPayment: 0
    };
    
    showAddForm = false;
  }

  function removeDebt(debtId: number) {
    debts = debts.filter(debt => debt.id !== debtId);
  }

  function toggleDebtStatus(debtId: number) {
    debts = debts.map(debt => 
      debt.id === debtId 
        ? { ...debt, isActive: !debt.isActive }
        : debt
    );
  }

  function calculatePaymentSchedule() {
    if (debts.filter(d => d.isActive).length === 0) {
      alert('Please add at least one active debt to calculate the payment schedule.');
      return;
    }

    const activeDebts = debts.filter(d => d.isActive).sort((a, b) => a.balance - b.balance); // Snowball: smallest balance first
    const schedule: PaymentSchedule[] = [];
    
    // Create copies of debts for calculation
    let currentDebts = activeDebts.map(debt => ({
      ...debt,
      remainingBalance: debt.balance,
      isPaidOff: false
    }));

    let month = 1;
    const startDate = new Date();
    
    while (currentDebts.some(d => !d.isPaidOff)) {
      const currentDate = new Date(startDate);
      currentDate.setMonth(startDate.getMonth() + month - 1);
      
      const monthSchedule: PaymentSchedule = {
        month,
        date: currentDate.toLocaleDateString('en-US', { 
          year: 'numeric', 
          month: 'short' 
        }),
        totalPayment: 0,
        debts: [],
        totalPrincipal: 0,
        totalInterest: 0,
        totalRemainingBalance: 0
      };

      // Calculate minimum payments for all debts
      let totalMinimumPayment = 0;
      currentDebts.forEach(debt => {
        if (!debt.isPaidOff) {
          totalMinimumPayment += debt.minimumPayment;
        }
      });

      // Add additional payment to the smallest debt
      let extraPayment = additionalMonthlyPayment;
      let totalPaymentThisMonth = totalMinimumPayment + additionalMonthlyPayment;

      // Process each debt in snowball order
      for (let i = 0; i < currentDebts.length; i++) {
        const debt = currentDebts[i];
        
        if (debt.isPaidOff) {
          monthSchedule.debts.push({
            debtId: debt.id,
            debtName: debt.name,
            payment: 0,
            principal: 0,
            interest: 0,
            remainingBalance: 0,
            isPaidOff: true
          });
          continue;
        }

        // Calculate interest for this month
        const monthlyInterestRate = debt.interestRate / 100 / 12;
        const interest = debt.remainingBalance * monthlyInterestRate;
        
        // Determine payment amount
        let payment = debt.minimumPayment;
        if (i === 0) { // Smallest debt gets extra payment
          payment += extraPayment;
        }
        
        // Calculate principal payment
        let principal = payment - interest;
        if (principal > debt.remainingBalance) {
          principal = debt.remainingBalance;
          payment = principal + interest;
        }
        
        // Update remaining balance
        const newBalance = debt.remainingBalance - principal;
        const isPaidOff = newBalance <= 0;
        
        // Update debt
        currentDebts[i] = {
          ...debt,
          remainingBalance: Math.max(0, newBalance),
          isPaidOff
        };

        // Add to schedule
        monthSchedule.debts.push({
          debtId: debt.id,
          debtName: debt.name,
          payment,
          principal,
          interest,
          remainingBalance: Math.max(0, newBalance),
          isPaidOff
        });

        monthSchedule.totalPayment += payment;
        monthSchedule.totalPrincipal += principal;
        monthSchedule.totalInterest += interest;
        monthSchedule.totalRemainingBalance += Math.max(0, newBalance);
      }

      schedule.push(monthSchedule);
      month++;

      // Stop if we've been calculating for too long (safety check)
      if (month > 600) { // 50 years
        break;
      }
    }

    paymentSchedule = schedule;
    showSchedule = true;
  }

  function exportSchedule() {
    const csvContent = generateCSV();
    const blob = new Blob([csvContent], { type: 'text/csv' });
    const url = window.URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'debt-payment-schedule.csv';
    a.click();
    window.URL.revokeObjectURL(url);
  }

  function generateCSV(): string {
    let csv = 'Month,Date,Total Payment,Total Principal,Total Interest,Total Remaining Balance\n';
    
    paymentSchedule.forEach(month => {
      csv += `${month.month},${month.date},${month.totalPayment.toFixed(2)},${month.totalPrincipal.toFixed(2)},${month.totalInterest.toFixed(2)},${month.totalRemainingBalance.toFixed(2)}\n`;
    });
    
    return csv;
  }

  function printSchedule() {
    window.print();
  }

  // Calculate summary statistics
  $: totalDebt = debts.filter(d => d.isActive).reduce((sum, debt) => sum + debt.balance, 0);
  $: totalMinimumPayments = debts.filter(d => d.isActive).reduce((sum, debt) => sum + debt.minimumPayment, 0);
  $: averageInterestRate = debts.filter(d => d.isActive).length > 0 
    ? debts.filter(d => d.isActive).reduce((sum, debt) => sum + debt.interestRate, 0) / debts.filter(d => d.isActive).length 
    : 0;
</script>

<RoleGuard resource="debt-calculator" action="read" fallback="You need permission to access the debt calculator.">
  <section class="debt-calculator">
    <div class="calculator-header">
      <h1>Debt Reduction Calculator</h1>
      <p>Use the debt snowball method to pay off your debts efficiently</p>
    </div>

    <div class="calculator-summary">
      <div class="summary-card">
        <h3>Total Debt</h3>
        <p class="amount">${totalDebt.toLocaleString()}</p>
      </div>
      <div class="summary-card">
        <h3>Monthly Minimum Payments</h3>
        <p class="amount">${totalMinimumPayments.toLocaleString()}</p>
      </div>
      <div class="summary-card">
        <h3>Average Interest Rate</h3>
        <p class="amount">{averageInterestRate.toFixed(2)}%</p>
      </div>
      <div class="summary-card">
        <h3>Additional Payment</h3>
        <p class="amount">${additionalMonthlyPayment.toLocaleString()}</p>
      </div>
    </div>

    <div class="calculator-controls">
      <div class="additional-payment">
        <label for="additional-payment">Additional Monthly Payment ($)</label>
        <input 
          id="additional-payment"
          type="number" 
          bind:value={additionalMonthlyPayment} 
          min="0" 
          step="50"
          placeholder="300"
        />
      </div>

      <div class="control-buttons">
        <button class="add-debt-btn" on:click={() => showAddForm = true}>
          Add Debt
        </button>
        <button class="calculate-btn" on:click={calculatePaymentSchedule}>
          Calculate Schedule
        </button>
      </div>
    </div>

    {#if showAddForm}
      <div class="add-debt-form">
        <div class="form-header">
          <h3>Add New Debt</h3>
          <button class="close-btn" on:click={() => showAddForm = false}>×</button>
        </div>
        
        <form on:submit|preventDefault={addDebt}>
          <div class="form-grid">
            <div class="form-group">
              <label for="debt-name">Debt Name *</label>
              <input 
                id="debt-name"
                type="text" 
                bind:value={newDebt.name} 
                required
                placeholder="e.g., Credit Card, Personal Loan"
              />
            </div>
            
            <div class="form-group">
              <label for="debt-type">Debt Type *</label>
              <select id="debt-type" bind:value={newDebt.type} required>
                <option value="credit-card">Credit Card</option>
                <option value="loan">Loan</option>
              </select>
            </div>
            
            <div class="form-group">
              <label for="balance">Current Balance ($) *</label>
              <input 
                id="balance"
                type="number" 
                bind:value={newDebt.balance} 
                required
                min="0"
                step="0.01"
                placeholder="5000"
              />
            </div>
            
            <div class="form-group">
              <label for="interest-rate">Interest Rate (%) *</label>
              <input 
                id="interest-rate"
                type="number" 
                bind:value={newDebt.interestRate} 
                required
                min="0"
                max="100"
                step="0.01"
                placeholder="18.99"
              />
            </div>
            
            <div class="form-group">
              <label for="minimum-payment">Minimum Payment ($) *</label>
              <input 
                id="minimum-payment"
                type="number" 
                bind:value={newDebt.minimumPayment} 
                required
                min="0"
                step="0.01"
                placeholder="150"
              />
            </div>
          </div>
          
          <div class="form-actions">
            <button type="button" class="cancel-btn" on:click={() => showAddForm = false}>
              Cancel
            </button>
            <button type="submit" class="save-btn">
              Add Debt
            </button>
          </div>
        </form>
      </div>
    {/if}

    <div class="debts-list">
      <h2>Your Debts</h2>
      {#if debts.filter(d => d.isActive).length === 0}
        <div class="empty-state">
          <h3>No active debts</h3>
          <p>Add your first debt to get started with the debt snowball method.</p>
        </div>
      {:else}
        <div class="debts-grid">
          {#each debts.filter(d => d.isActive).sort((a, b) => a.balance - b.balance) as debt, index}
            <div class="debt-card" class:snowball-order={index === 0}>
              <div class="debt-header">
                <h3>{debt.name}</h3>
                <div class="debt-badges">
                  <span class="badge type">{debt.type === 'credit-card' ? 'Credit Card' : 'Loan'}</span>
                  {#if index === 0}
                    <span class="badge snowball">Snowball #1</span>
                  {/if}
                </div>
              </div>
              
              <div class="debt-details">
                <div class="detail">
                  <span class="label">Balance:</span>
                  <span class="value">${debt.balance.toLocaleString()}</span>
                </div>
                <div class="detail">
                  <span class="label">Interest Rate:</span>
                  <span class="value">{debt.interestRate}%</span>
                </div>
                <div class="detail">
                  <span class="label">Minimum Payment:</span>
                  <span class="value">${debt.minimumPayment.toLocaleString()}</span>
                </div>
              </div>
              
              <div class="debt-actions">
                <button 
                  class="action-btn deactivate" 
                  on:click={() => toggleDebtStatus(debt.id)}
                >
                  Deactivate
                </button>
                <button 
                  class="action-btn delete" 
                  on:click={() => removeDebt(debt.id)}
                >
                  Delete
                </button>
              </div>
            </div>
          {/each}
        </div>
      {/if}
    </div>

    {#if showSchedule && paymentSchedule.length > 0}
      <div class="payment-schedule">
        <div class="schedule-header">
          <h2>Payment Schedule</h2>
          <div class="schedule-actions">
            <button class="export-btn" on:click={exportSchedule}>Export CSV</button>
            <button class="print-btn" on:click={printSchedule}>Print</button>
          </div>
        </div>

        <div class="schedule-summary">
          <div class="summary-item">
            <span>Total Months to Payoff:</span>
            <span class="value">{paymentSchedule.length}</span>
          </div>
          <div class="summary-item">
            <span>Total Interest Paid:</span>
            <span class="value">${paymentSchedule.reduce((sum, month) => sum + month.totalInterest, 0).toLocaleString()}</span>
          </div>
          <div class="summary-item">
            <span>Total Amount Paid:</span>
            <span class="value">${paymentSchedule.reduce((sum, month) => sum + month.totalPayment, 0).toLocaleString()}</span>
          </div>
        </div>

        <div class="schedule-table">
          <table>
            <thead>
              <tr>
                <th>Month</th>
                <th>Date</th>
                <th>Total Payment</th>
                <th>Principal</th>
                <th>Interest</th>
                <th>Remaining Balance</th>
              </tr>
            </thead>
            <tbody>
              {#each paymentSchedule as month}
                <tr>
                  <td>{month.month}</td>
                  <td>{month.date}</td>
                  <td>${month.totalPayment.toFixed(2)}</td>
                  <td>${month.totalPrincipal.toFixed(2)}</td>
                  <td>${month.totalInterest.toFixed(2)}</td>
                  <td>${month.totalRemainingBalance.toFixed(2)}</td>
                </tr>
              {/each}
            </tbody>
          </table>
        </div>
      </div>
    {/if}
  </section>
</RoleGuard>

<style>
  .debt-calculator {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .calculator-header {
    text-align: center;
    margin-bottom: 2rem;
  }

  .calculator-header h1 {
    font-size: 2rem;
    margin-bottom: 0.5rem;
    color: #333;
  }

  .calculator-header p {
    color: #666;
    font-size: 1.1rem;
  }

  .calculator-summary {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
    margin-bottom: 2rem;
  }

  .summary-card {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
    text-align: center;
  }

  .summary-card h3 {
    margin: 0 0 0.5rem 0;
    color: #666;
    font-size: 0.9rem;
    text-transform: uppercase;
    letter-spacing: 0.5px;
  }

  .summary-card .amount {
    margin: 0;
    font-size: 1.5rem;
    font-weight: 600;
    color: #333;
  }

  .calculator-controls {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
    margin-bottom: 2rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
    gap: 1rem;
  }

  .additional-payment {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }

  .additional-payment label {
    font-weight: 500;
    color: #333;
  }

  .additional-payment input {
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
    width: 200px;
  }

  .control-buttons {
    display: flex;
    gap: 1rem;
  }

  .add-debt-btn,
  .calculate-btn {
    padding: 0.75rem 1.5rem;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .add-debt-btn {
    background: #17a2b8;
    color: white;
  }

  .add-debt-btn:hover {
    background: #138496;
  }

  .calculate-btn {
    background: #28a745;
    color: white;
  }

  .calculate-btn:hover {
    background: #218838;
  }

  .add-debt-form {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
    margin-bottom: 2rem;
  }

  .form-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 1.5rem;
  }

  .form-header h3 {
    margin: 0;
    color: #333;
  }

  .close-btn {
    background: none;
    border: none;
    font-size: 1.5rem;
    cursor: pointer;
    color: #666;
    padding: 0;
    width: 30px;
    height: 30px;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .close-btn:hover {
    color: #333;
  }

  .form-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
    margin-bottom: 1.5rem;
  }

  .form-group label {
    display: block;
    margin-bottom: 0.5rem;
    font-weight: 500;
    color: #333;
  }

  .form-group input,
  .form-group select {
    width: 100%;
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
  }

  .form-actions {
    display: flex;
    gap: 1rem;
    justify-content: flex-end;
  }

  .cancel-btn,
  .save-btn {
    padding: 0.75rem 1.5rem;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .cancel-btn {
    background: #6c757d;
    color: white;
  }

  .cancel-btn:hover {
    background: #545b62;
  }

  .save-btn {
    background: #28a745;
    color: white;
  }

  .save-btn:hover {
    background: #218838;
  }

  .debts-list {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
    margin-bottom: 2rem;
  }

  .debts-list h2 {
    margin: 0 0 1.5rem 0;
    color: #333;
  }

  .debts-grid {
    display: grid;
    gap: 1rem;
  }

  .debt-card {
    border: 1px solid #e9ecef;
    border-radius: 8px;
    padding: 1.5rem;
    transition: all 0.2s;
  }

  .debt-card:hover {
    box-shadow: 0 4px 12px rgba(0,0,0,0.1);
  }

  .debt-card.snowball-order {
    border: 2px solid #28a745;
    background: #f8fff9;
  }

  .debt-header {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    margin-bottom: 1rem;
  }

  .debt-header h3 {
    margin: 0;
    color: #333;
    font-size: 1.1rem;
  }

  .debt-badges {
    display: flex;
    gap: 0.5rem;
    flex-wrap: wrap;
  }

  .badge {
    padding: 0.25rem 0.5rem;
    border-radius: 4px;
    font-size: 0.75rem;
    font-weight: 500;
  }

  .badge.type {
    background: #17a2b8;
    color: white;
  }

  .badge.snowball {
    background: #28a745;
    color: white;
  }

  .debt-details {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
    gap: 0.5rem;
    margin-bottom: 1rem;
  }

  .detail {
    display: flex;
    justify-content: space-between;
  }

  .detail .label {
    font-weight: 500;
    color: #666;
  }

  .detail .value {
    color: #333;
  }

  .debt-actions {
    display: flex;
    gap: 0.5rem;
  }

  .action-btn {
    padding: 0.5rem 1rem;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
    font-weight: 500;
    transition: background-color 0.2s;
    flex: 1;
  }

  .action-btn.deactivate {
    background: #ffc107;
    color: #212529;
  }

  .action-btn.deactivate:hover {
    background: #e0a800;
  }

  .action-btn.delete {
    background: #dc3545;
    color: white;
  }

  .action-btn.delete:hover {
    background: #c82333;
  }

  .empty-state {
    text-align: center;
    padding: 3rem;
    color: #666;
  }

  .empty-state h3 {
    margin-bottom: 0.5rem;
  }

  .payment-schedule {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
  }

  .schedule-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 1.5rem;
  }

  .schedule-header h2 {
    margin: 0;
    color: #333;
  }

  .schedule-actions {
    display: flex;
    gap: 1rem;
  }

  .export-btn,
  .print-btn {
    padding: 0.5rem 1rem;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
    font-weight: 500;
    transition: background-color 0.2s;
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

  .schedule-summary {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
    margin-bottom: 1.5rem;
    padding: 1rem;
    background: #f8f9fa;
    border-radius: 6px;
  }

  .summary-item {
    display: flex;
    justify-content: space-between;
    align-items: center;
  }

  .summary-item span:first-child {
    font-weight: 500;
    color: #666;
  }

  .summary-item .value {
    font-weight: 600;
    color: #333;
  }

  .schedule-table {
    overflow-x: auto;
  }

  .schedule-table table {
    width: 100%;
    border-collapse: collapse;
  }

  .schedule-table th,
  .schedule-table td {
    padding: 0.75rem;
    text-align: left;
    border-bottom: 1px solid #e9ecef;
  }

  .schedule-table th {
    background: #f8f9fa;
    font-weight: 600;
    color: #333;
  }

  .schedule-table tr:hover {
    background: #f8f9fa;
  }

  @media (max-width: 768px) {
    .calculator-controls {
      flex-direction: column;
      align-items: stretch;
    }

    .additional-payment input {
      width: 100%;
    }

    .control-buttons {
      justify-content: stretch;
    }

    .form-grid {
      grid-template-columns: 1fr;
    }

    .debt-header {
      flex-direction: column;
      align-items: flex-start;
      gap: 0.5rem;
    }

    .debt-actions {
      flex-direction: column;
    }

    .schedule-header {
      flex-direction: column;
      align-items: flex-start;
      gap: 1rem;
    }

    .schedule-actions {
      width: 100%;
      justify-content: stretch;
    }

    .export-btn,
    .print-btn {
      flex: 1;
    }
  }

  @media print {
    .calculator-controls,
    .add-debt-form,
    .debts-list,
    .schedule-actions {
      display: none;
    }
  }
</style> 