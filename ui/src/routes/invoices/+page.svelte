<script lang="ts">
  import { auth } from '$lib/auth';
  import RoleGuard from '$lib/RoleGuard.svelte';

  interface InvoiceItem {
    id: number;
    description: string;
    quantity: number;
    unitPrice: number;
    amount: number;
  }

  interface Invoice {
    id: number;
    invoiceNumber: string;
    customerName: string;
    customerEmail: string;
    customerAddress: string;
    issueDate: string;
    dueDate: string;
    items: InvoiceItem[];
    subtotal: number;
    taxRate: number;
    taxAmount: number;
    total: number;
    status: 'draft' | 'sent' | 'paid' | 'overdue' | 'cancelled';
    notes: string;
    terms: string;
  }

  let invoices: Invoice[] = [
    {
      id: 1,
      invoiceNumber: 'INV-2024-001',
      customerName: 'Acme Corporation',
      customerEmail: 'accounts@acme.com',
      customerAddress: '123 Business St, City, State 12345',
      issueDate: '2024-01-15',
      dueDate: '2024-02-15',
      items: [
        {
          id: 1,
          description: 'Web Development Services',
          quantity: 40,
          unitPrice: 75,
          amount: 3000
        },
        {
          id: 2,
          description: 'SEO Optimization',
          quantity: 1,
          unitPrice: 500,
          amount: 500
        }
      ],
      subtotal: 3500,
      taxRate: 8.5,
      taxAmount: 297.50,
      total: 3797.50,
      status: 'paid',
      notes: 'Thank you for your business!',
      terms: 'Net 30 days'
    },
    {
      id: 2,
      invoiceNumber: 'INV-2024-002',
      customerName: 'TechStart LLC',
      customerEmail: 'finance@techstart.com',
      customerAddress: '456 Innovation Ave, Tech City, TC 67890',
      issueDate: '2024-01-20',
      dueDate: '2024-02-20',
      items: [
        {
          id: 1,
          description: 'Consulting Services',
          quantity: 25,
          unitPrice: 120,
          amount: 3000
        }
      ],
      subtotal: 3000,
      taxRate: 8.5,
      taxAmount: 255,
      total: 3255,
      status: 'sent',
      notes: 'Please remit payment within 30 days.',
      terms: 'Net 30 days'
    },
    {
      id: 3,
      invoiceNumber: 'INV-2024-003',
      customerName: 'Global Manufacturing Inc',
      customerEmail: 'ap@globalmfg.com',
      customerAddress: '789 Industrial Blvd, Factory Town, FT 13579',
      issueDate: '2024-01-10',
      dueDate: '2024-02-10',
      items: [
        {
          id: 1,
          description: 'Software Implementation',
          quantity: 1,
          unitPrice: 15000,
          amount: 15000
        },
        {
          id: 2,
          description: 'Training Sessions',
          quantity: 8,
          unitPrice: 250,
          amount: 2000
        }
      ],
      subtotal: 17000,
      taxRate: 8.5,
      taxAmount: 1445,
      total: 18445,
      status: 'overdue',
      notes: 'Payment is overdue. Please contact us immediately.',
      terms: 'Net 30 days'
    }
  ];

  let showCreateForm = false;
  let selectedInvoice: Invoice | null = null;
  let showInvoiceView = false;
  let searchTerm = '';
  let selectedStatus = 'all';
  let selectedCustomer = 'all';

  // New invoice form data
  let newInvoice = {
    customerName: '',
    customerEmail: '',
    customerAddress: '',
    issueDate: new Date().toISOString().split('T')[0],
    dueDate: new Date(Date.now() + 30 * 24 * 60 * 60 * 1000).toISOString().split('T')[0],
    items: [
      {
        id: 1,
        description: '',
        quantity: 1,
        unitPrice: 0,
        amount: 0
      }
    ],
    taxRate: 8.5,
    notes: '',
    terms: 'Net 30 days'
  };

  // Calculate invoice totals
  $: newInvoice.items.forEach(item => {
    item.amount = item.quantity * item.unitPrice;
  });

  $: newInvoiceSubtotal = newInvoice.items.reduce((sum, item) => sum + item.amount, 0);
  $: newInvoiceTaxAmount = newInvoiceSubtotal * (newInvoice.taxRate / 100);
  $: newInvoiceTotal = newInvoiceSubtotal + newInvoiceTaxAmount;

  // Filter invoices
  $: filteredInvoices = invoices.filter(invoice => {
    const matchesSearch = invoice.invoiceNumber.toLowerCase().includes(searchTerm.toLowerCase()) ||
                         invoice.customerName.toLowerCase().includes(searchTerm.toLowerCase());
    const matchesStatus = selectedStatus === 'all' || invoice.status === selectedStatus;
    const matchesCustomer = selectedCustomer === 'all' || invoice.customerName === selectedCustomer;
    
    return matchesSearch && matchesStatus && matchesCustomer;
  });

  // Get unique customers for filter
  $: customers = [...new Set(invoices.map(invoice => invoice.customerName))];

  function generateInvoiceNumber(): string {
    const year = new Date().getFullYear();
    const nextNumber = invoices.length + 1;
    return `INV-${year}-${nextNumber.toString().padStart(3, '0')}`;
  }

  function addInvoiceItem() {
    const newId = Math.max(...newInvoice.items.map(item => item.id)) + 1;
    newInvoice.items = [...newInvoice.items, {
      id: newId,
      description: '',
      quantity: 1,
      unitPrice: 0,
      amount: 0
    }];
  }

  function removeInvoiceItem(itemId: number) {
    if (newInvoice.items.length > 1) {
      newInvoice.items = newInvoice.items.filter(item => item.id !== itemId);
    }
  }

  function createInvoice() {
    const invoice: Invoice = {
      id: Math.max(...invoices.map(inv => inv.id)) + 1,
      invoiceNumber: generateInvoiceNumber(),
      customerName: newInvoice.customerName,
      customerEmail: newInvoice.customerEmail,
      customerAddress: newInvoice.customerAddress,
      issueDate: newInvoice.issueDate,
      dueDate: newInvoice.dueDate,
      items: [...newInvoice.items],
      subtotal: newInvoiceSubtotal,
      taxRate: newInvoice.taxRate,
      taxAmount: newInvoiceTaxAmount,
      total: newInvoiceTotal,
      status: 'draft',
      notes: newInvoice.notes,
      terms: newInvoice.terms
    };

    invoices = [...invoices, invoice];
    
    // Reset form
    newInvoice = {
      customerName: '',
      customerEmail: '',
      customerAddress: '',
      issueDate: new Date().toISOString().split('T')[0],
      dueDate: new Date(Date.now() + 30 * 24 * 60 * 60 * 1000).toISOString().split('T')[0],
      items: [
        {
          id: 1,
          description: '',
          quantity: 1,
          unitPrice: 0,
          amount: 0
        }
      ],
      taxRate: 8.5,
      notes: '',
      terms: 'Net 30 days'
    };
    
    showCreateForm = false;
  }

  function viewInvoice(invoice: Invoice) {
    selectedInvoice = invoice;
    showInvoiceView = true;
  }

  function updateInvoiceStatus(invoiceId: number, status: Invoice['status']) {
    invoices = invoices.map(invoice => 
      invoice.id === invoiceId 
        ? { ...invoice, status }
        : invoice
    );
  }

  function deleteInvoice(invoiceId: number) {
    if (confirm('Are you sure you want to delete this invoice? This action cannot be undone.')) {
      invoices = invoices.filter(invoice => invoice.id !== invoiceId);
    }
  }

  function printInvoice(invoice: Invoice) {
    selectedInvoice = invoice;
    showInvoiceView = true;
    setTimeout(() => {
      window.print();
    }, 100);
  }

  function getStatusColor(status: Invoice['status']): string {
    switch (status) {
      case 'draft': return '#6c757d';
      case 'sent': return '#17a2b8';
      case 'paid': return '#28a745';
      case 'overdue': return '#dc3545';
      case 'cancelled': return '#6c757d';
      default: return '#6c757d';
    }
  }

  function getStatusLabel(status: Invoice['status']): string {
    switch (status) {
      case 'draft': return 'Draft';
      case 'sent': return 'Sent';
      case 'paid': return 'Paid';
      case 'overdue': return 'Overdue';
      case 'cancelled': return 'Cancelled';
      default: return status;
    }
  }
</script>

<RoleGuard resource="invoices" action="read" fallback="You need permission to access invoices.">
  <section class="invoices">
    <div class="invoices-header">
      <h1>Invoices</h1>
      <p>Create, manage, and track invoices for your customers</p>
    </div>

    <div class="invoices-controls">
      <div class="search-filters">
        <div class="search-box">
          <input 
            type="text" 
            placeholder="Search invoices..." 
            bind:value={searchTerm}
          />
        </div>
        
        <div class="filters">
          <select bind:value={selectedStatus}>
            <option value="all">All Status</option>
            <option value="draft">Draft</option>
            <option value="sent">Sent</option>
            <option value="paid">Paid</option>
            <option value="overdue">Overdue</option>
            <option value="cancelled">Cancelled</option>
          </select>
          
          <select bind:value={selectedCustomer}>
            <option value="all">All Customers</option>
            {#each customers as customer}
              <option value={customer}>{customer}</option>
            {/each}
          </select>
        </div>
      </div>

      <button class="create-btn" on:click={() => showCreateForm = true}>
        Create Invoice
      </button>
    </div>

    {#if showCreateForm}
      <div class="create-invoice-form">
        <div class="form-header">
          <h3>Create New Invoice</h3>
          <button class="close-btn" on:click={() => showCreateForm = false}>×</button>
        </div>
        
        <form on:submit|preventDefault={createInvoice}>
          <div class="form-grid">
            <div class="form-group">
              <label for="customer-name">Customer Name *</label>
              <input 
                id="customer-name"
                type="text" 
                bind:value={newInvoice.customerName} 
                required
                placeholder="Enter customer name"
              />
            </div>
            
            <div class="form-group">
              <label for="customer-email">Customer Email</label>
              <input 
                id="customer-email"
                type="email" 
                bind:value={newInvoice.customerEmail} 
                placeholder="customer@example.com"
              />
            </div>
            
            <div class="form-group">
              <label for="issue-date">Issue Date *</label>
              <input 
                id="issue-date"
                type="date" 
                bind:value={newInvoice.issueDate} 
                required
              />
            </div>
            
            <div class="form-group">
              <label for="due-date">Due Date *</label>
              <input 
                id="due-date"
                type="date" 
                bind:value={newInvoice.dueDate} 
                required
              />
            </div>
            
            <div class="form-group full-width">
              <label for="customer-address">Customer Address</label>
              <textarea 
                id="customer-address"
                bind:value={newInvoice.customerAddress} 
                placeholder="Enter customer address"
                rows="3"
              ></textarea>
            </div>
          </div>

          <div class="invoice-items">
            <div class="items-header">
              <h4>Invoice Items</h4>
              <button type="button" class="add-item-btn" on:click={addInvoiceItem}>
                Add Item
              </button>
            </div>
            
            <div class="items-table">
              <table>
                <thead>
                  <tr>
                    <th>Description</th>
                    <th>Quantity</th>
                    <th>Unit Price</th>
                    <th>Amount</th>
                    <th>Action</th>
                  </tr>
                </thead>
                <tbody>
                  {#each newInvoice.items as item}
                    <tr>
                      <td>
                        <input 
                          type="text" 
                          bind:value={item.description} 
                          placeholder="Item description"
                          required
                        />
                      </td>
                      <td>
                        <input 
                          type="number" 
                          bind:value={item.quantity} 
                          min="1"
                          required
                        />
                      </td>
                      <td>
                        <input 
                          type="number" 
                          bind:value={item.unitPrice} 
                          min="0"
                          step="0.01"
                          required
                        />
                      </td>
                      <td>
                        <span class="amount">${item.amount.toFixed(2)}</span>
                      </td>
                      <td>
                        {#if newInvoice.items.length > 1}
                          <button 
                            type="button" 
                            class="remove-item-btn" 
                            on:click={() => removeInvoiceItem(item.id)}
                          >
                            ×
                          </button>
                        {/if}
                      </td>
                    </tr>
                  {/each}
                </tbody>
              </table>
            </div>
          </div>

          <div class="invoice-summary">
            <div class="summary-row">
              <span>Subtotal:</span>
              <span>${newInvoiceSubtotal.toFixed(2)}</span>
            </div>
            <div class="summary-row">
              <span>Tax Rate (%):</span>
              <input 
                type="number" 
                bind:value={newInvoice.taxRate} 
                min="0"
                max="100"
                step="0.01"
                class="tax-rate-input"
              />
            </div>
            <div class="summary-row">
              <span>Tax Amount:</span>
              <span>${newInvoiceTaxAmount.toFixed(2)}</span>
            </div>
            <div class="summary-row total">
              <span>Total:</span>
              <span>${newInvoiceTotal.toFixed(2)}</span>
            </div>
          </div>

          <div class="form-grid">
            <div class="form-group">
              <label for="terms">Payment Terms</label>
              <input 
                id="terms"
                type="text" 
                bind:value={newInvoice.terms} 
                placeholder="Net 30 days"
              />
            </div>
            
            <div class="form-group">
              <label for="notes">Notes</label>
              <textarea 
                id="notes"
                bind:value={newInvoice.notes} 
                placeholder="Additional notes"
                rows="3"
              ></textarea>
            </div>
          </div>
          
          <div class="form-actions">
            <button type="button" class="cancel-btn" on:click={() => showCreateForm = false}>
              Cancel
            </button>
            <button type="submit" class="save-btn">
              Create Invoice
            </button>
          </div>
        </form>
      </div>
    {/if}

    <div class="invoices-list">
      {#if filteredInvoices.length === 0}
        <div class="empty-state">
          <h3>No invoices found</h3>
          <p>Try adjusting your search criteria or create a new invoice.</p>
        </div>
      {:else}
        <div class="invoices-table">
          <table>
            <thead>
              <tr>
                <th>Invoice #</th>
                <th>Customer</th>
                <th>Issue Date</th>
                <th>Due Date</th>
                <th>Amount</th>
                <th>Status</th>
                <th>Actions</th>
              </tr>
            </thead>
            <tbody>
              {#each filteredInvoices as invoice}
                <tr>
                  <td>
                    <a href="#" on:click|preventDefault={() => viewInvoice(invoice)}>
                      {invoice.invoiceNumber}
                    </a>
                  </td>
                  <td>{invoice.customerName}</td>
                  <td>{new Date(invoice.issueDate).toLocaleDateString()}</td>
                  <td>{new Date(invoice.dueDate).toLocaleDateString()}</td>
                  <td>${invoice.total.toFixed(2)}</td>
                  <td>
                    <span class="status-badge" style="background-color: {getStatusColor(invoice.status)}">
                      {getStatusLabel(invoice.status)}
                    </span>
                  </td>
                  <td>
                    <div class="action-buttons">
                      <button 
                        class="action-btn view" 
                        on:click={() => viewInvoice(invoice)}
                        title="View Invoice"
                      >
                        👁️
                      </button>
                      <button 
                        class="action-btn print" 
                        on:click={() => printInvoice(invoice)}
                        title="Print Invoice"
                      >
                        🖨️
                      </button>
                      <select 
                        class="status-select" 
                        value={invoice.status}
                        on:change={(e) => updateInvoiceStatus(invoice.id, e.target.value as Invoice['status'])}
                      >
                        <option value="draft">Draft</option>
                        <option value="sent">Sent</option>
                        <option value="paid">Paid</option>
                        <option value="overdue">Overdue</option>
                        <option value="cancelled">Cancelled</option>
                      </select>
                      <button 
                        class="action-btn delete" 
                        on:click={() => deleteInvoice(invoice.id)}
                        title="Delete Invoice"
                      >
                        🗑️
                      </button>
                    </div>
                  </td>
                </tr>
              {/each}
            </tbody>
          </table>
        </div>
      {/if}
    </div>

    {#if showInvoiceView && selectedInvoice}
      <div class="invoice-view-modal">
        <div class="modal-content">
          <div class="modal-header">
            <h2>Invoice {selectedInvoice.invoiceNumber}</h2>
            <button class="close-btn" on:click={() => showInvoiceView = false}>×</button>
          </div>
          
          <div class="invoice-document">
            <div class="invoice-header">
              <div class="company-info">
                <h1>PentaLedger</h1>
                <p>123 Accounting Street<br>Business City, BC 12345<br>Phone: (555) 123-4567</p>
              </div>
              <div class="invoice-info">
                <h2>INVOICE</h2>
                <p><strong>Invoice #:</strong> {selectedInvoice.invoiceNumber}</p>
                <p><strong>Issue Date:</strong> {new Date(selectedInvoice.issueDate).toLocaleDateString()}</p>
                <p><strong>Due Date:</strong> {new Date(selectedInvoice.dueDate).toLocaleDateString()}</p>
                <p><strong>Status:</strong> {getStatusLabel(selectedInvoice.status)}</p>
              </div>
            </div>
            
            <div class="invoice-body">
              <div class="customer-info">
                <h3>Bill To:</h3>
                <p><strong>{selectedInvoice.customerName}</strong></p>
                {#if selectedInvoice.customerEmail}
                  <p>{selectedInvoice.customerEmail}</p>
                {/if}
                {#if selectedInvoice.customerAddress}
                  <p>{selectedInvoice.customerAddress}</p>
                {/if}
              </div>
              
              <div class="invoice-items">
                <table>
                  <thead>
                    <tr>
                      <th>Description</th>
                      <th>Quantity</th>
                      <th>Unit Price</th>
                      <th>Amount</th>
                    </tr>
                  </thead>
                  <tbody>
                    {#each selectedInvoice.items as item}
                      <tr>
                        <td>{item.description}</td>
                        <td>{item.quantity}</td>
                        <td>${item.unitPrice.toFixed(2)}</td>
                        <td>${item.amount.toFixed(2)}</td>
                      </tr>
                    {/each}
                  </tbody>
                </table>
              </div>
              
              <div class="invoice-summary">
                <div class="summary-row">
                  <span>Subtotal:</span>
                  <span>${selectedInvoice.subtotal.toFixed(2)}</span>
                </div>
                <div class="summary-row">
                  <span>Tax ({selectedInvoice.taxRate}%):</span>
                  <span>${selectedInvoice.taxAmount.toFixed(2)}</span>
                </div>
                <div class="summary-row total">
                  <span>Total:</span>
                  <span>${selectedInvoice.total.toFixed(2)}</span>
                </div>
              </div>
              
              {#if selectedInvoice.notes}
                <div class="invoice-notes">
                  <h4>Notes:</h4>
                  <p>{selectedInvoice.notes}</p>
                </div>
              {/if}
              
              <div class="invoice-terms">
                <h4>Payment Terms:</h4>
                <p>{selectedInvoice.terms}</p>
              </div>
            </div>
          </div>
          
          <div class="modal-actions">
            <button class="print-btn" on:click={() => window.print()}>Print Invoice</button>
            <button class="close-modal-btn" on:click={() => showInvoiceView = false}>Close</button>
          </div>
        </div>
      </div>
    {/if}
  </section>
</RoleGuard>

<style>
  .invoices {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .invoices-header {
    text-align: center;
    margin-bottom: 2rem;
  }

  .invoices-header h1 {
    font-size: 2rem;
    margin-bottom: 0.5rem;
    color: #333;
  }

  .invoices-header p {
    color: #666;
    font-size: 1.1rem;
  }

  .invoices-controls {
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

  .search-filters {
    display: flex;
    gap: 1rem;
    align-items: center;
    flex: 1;
  }

  .search-box input {
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
    min-width: 250px;
  }

  .filters {
    display: flex;
    gap: 0.5rem;
  }

  .filters select {
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
  }

  .create-btn {
    padding: 0.75rem 1.5rem;
    background: #28a745;
    color: white;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .create-btn:hover {
    background: #218838;
  }

  .create-invoice-form {
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
    grid-template-columns: 1fr 1fr;
    gap: 1rem;
    margin-bottom: 1.5rem;
  }

  .form-group.full-width {
    grid-column: 1 / -1;
  }

  .form-group label {
    display: block;
    margin-bottom: 0.5rem;
    font-weight: 500;
    color: #333;
  }

  .form-group input,
  .form-group select,
  .form-group textarea {
    width: 100%;
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
  }

  .form-group textarea {
    resize: vertical;
  }

  .invoice-items {
    margin-bottom: 1.5rem;
  }

  .items-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 1rem;
  }

  .items-header h4 {
    margin: 0;
    color: #333;
  }

  .add-item-btn {
    padding: 0.5rem 1rem;
    background: #17a2b8;
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
  }

  .add-item-btn:hover {
    background: #138496;
  }

  .items-table table {
    width: 100%;
    border-collapse: collapse;
  }

  .items-table th,
  .items-table td {
    padding: 0.75rem;
    text-align: left;
    border-bottom: 1px solid #e9ecef;
  }

  .items-table th {
    background: #f8f9fa;
    font-weight: 600;
    color: #333;
  }

  .items-table input {
    width: 100%;
    padding: 0.5rem;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 0.875rem;
  }

  .amount {
    font-weight: 600;
    color: #333;
  }

  .remove-item-btn {
    background: #dc3545;
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    padding: 0.25rem 0.5rem;
    font-size: 1rem;
  }

  .remove-item-btn:hover {
    background: #c82333;
  }

  .invoice-summary {
    background: #f8f9fa;
    padding: 1rem;
    border-radius: 6px;
    margin-bottom: 1.5rem;
  }

  .summary-row {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0.5rem 0;
  }

  .summary-row.total {
    border-top: 2px solid #dee2e6;
    font-weight: 600;
    font-size: 1.1rem;
  }

  .tax-rate-input {
    width: 100px !important;
    text-align: right;
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

  .invoices-list {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    overflow: hidden;
  }

  .invoices-table {
    overflow-x: auto;
  }

  .invoices-table table {
    width: 100%;
    border-collapse: collapse;
  }

  .invoices-table th,
  .invoices-table td {
    padding: 1rem;
    text-align: left;
    border-bottom: 1px solid #e9ecef;
  }

  .invoices-table th {
    background: #f8f9fa;
    font-weight: 600;
    color: #333;
  }

  .invoices-table tr:hover {
    background: #f8f9fa;
  }

  .invoices-table a {
    color: #007bff;
    text-decoration: none;
    font-weight: 500;
  }

  .invoices-table a:hover {
    text-decoration: underline;
  }

  .status-badge {
    padding: 0.25rem 0.5rem;
    border-radius: 4px;
    color: white;
    font-size: 0.75rem;
    font-weight: 500;
  }

  .action-buttons {
    display: flex;
    gap: 0.5rem;
    align-items: center;
  }

  .action-btn {
    background: none;
    border: none;
    cursor: pointer;
    padding: 0.25rem;
    border-radius: 4px;
    transition: background-color 0.2s;
  }

  .action-btn:hover {
    background: #f8f9fa;
  }

  .status-select {
    padding: 0.25rem;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 0.75rem;
  }

  .empty-state {
    text-align: center;
    padding: 3rem;
    color: #666;
  }

  .empty-state h3 {
    margin-bottom: 0.5rem;
  }

  /* Invoice View Modal */
  .invoice-view-modal {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0,0,0,0.5);
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: 1000;
  }

  .modal-content {
    background: white;
    border-radius: 8px;
    max-width: 800px;
    width: 90%;
    max-height: 90vh;
    overflow-y: auto;
  }

  .modal-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 1.5rem;
    border-bottom: 1px solid #e9ecef;
  }

  .modal-header h2 {
    margin: 0;
    color: #333;
  }

  .invoice-document {
    padding: 1.5rem;
  }

  .invoice-header {
    display: flex;
    justify-content: space-between;
    margin-bottom: 2rem;
  }

  .company-info h1 {
    margin: 0 0 0.5rem 0;
    color: #333;
    font-size: 1.5rem;
  }

  .company-info p {
    margin: 0;
    color: #666;
    line-height: 1.5;
  }

  .invoice-info h2 {
    margin: 0 0 1rem 0;
    color: #333;
    font-size: 1.5rem;
  }

  .invoice-info p {
    margin: 0.25rem 0;
    color: #666;
  }

  .customer-info {
    margin-bottom: 2rem;
  }

  .customer-info h3 {
    margin: 0 0 0.5rem 0;
    color: #333;
  }

  .customer-info p {
    margin: 0.25rem 0;
    color: #666;
  }

  .invoice-items table {
    width: 100%;
    border-collapse: collapse;
    margin-bottom: 2rem;
  }

  .invoice-items th,
  .invoice-items td {
    padding: 0.75rem;
    text-align: left;
    border-bottom: 1px solid #e9ecef;
  }

  .invoice-items th {
    background: #f8f9fa;
    font-weight: 600;
    color: #333;
  }

  .invoice-summary {
    background: #f8f9fa;
    padding: 1rem;
    border-radius: 6px;
    margin-bottom: 2rem;
  }

  .invoice-notes,
  .invoice-terms {
    margin-bottom: 1rem;
  }

  .invoice-notes h4,
  .invoice-terms h4 {
    margin: 0 0 0.5rem 0;
    color: #333;
  }

  .invoice-notes p,
  .invoice-terms p {
    margin: 0;
    color: #666;
  }

  .modal-actions {
    display: flex;
    gap: 1rem;
    justify-content: flex-end;
    padding: 1.5rem;
    border-top: 1px solid #e9ecef;
  }

  .print-btn,
  .close-modal-btn {
    padding: 0.75rem 1.5rem;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .print-btn {
    background: #17a2b8;
    color: white;
  }

  .print-btn:hover {
    background: #138496;
  }

  .close-modal-btn {
    background: #6c757d;
    color: white;
  }

  .close-modal-btn:hover {
    background: #545b62;
  }

  @media (max-width: 768px) {
    .invoices-controls {
      flex-direction: column;
      align-items: stretch;
    }

    .search-filters {
      flex-direction: column;
      align-items: stretch;
    }

    .filters {
      justify-content: stretch;
    }

    .form-grid {
      grid-template-columns: 1fr;
    }

    .invoice-header {
      flex-direction: column;
      gap: 1rem;
    }

    .action-buttons {
      flex-direction: column;
      gap: 0.25rem;
    }

    .modal-content {
      width: 95%;
      margin: 1rem;
    }
  }

  @media print {
    .invoices-controls,
    .create-invoice-form,
    .invoices-list,
    .modal-header,
    .modal-actions {
      display: none;
    }

    .invoice-view-modal {
      position: static;
      background: none;
    }

    .modal-content {
      box-shadow: none;
      border: none;
    }

    .invoice-document {
      padding: 0;
    }
  }
</style> 