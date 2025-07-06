<script lang="ts">
  import { auth } from '$lib/auth';
  import RoleGuard from '$lib/RoleGuard.svelte';

  interface VendorTransaction {
    id: number;
    date: string;
    type: 'purchase' | 'payment' | 'credit' | 'refund';
    reference: string;
    description: string;
    amount: number;
    balance: number;
  }

  interface Vendor {
    id: number;
    name: string;
    contactPerson: string;
    email: string;
    phone: string;
    address: string;
    city: string;
    state: string;
    zipCode: string;
    country: string;
    taxId: string;
    paymentTerms: string;
    creditLimit: number;
    currentBalance: number;
    status: 'active' | 'inactive' | 'suspended';
    category: string;
    notes: string;
    transactions: VendorTransaction[];
  }

  let vendors: Vendor[] = [
    {
      id: 1,
      name: 'Office Supplies Plus',
      contactPerson: 'John Smith',
      email: 'john@officesuppliesplus.com',
      phone: '(555) 123-4567',
      address: '123 Supply Street',
      city: 'Business City',
      state: 'BC',
      zipCode: '12345',
      country: 'USA',
      taxId: '12-3456789',
      paymentTerms: 'Net 30',
      creditLimit: 10000,
      currentBalance: 2500,
      status: 'active',
      category: 'Office Supplies',
      notes: 'Primary office supplies vendor',
      transactions: [
        {
          id: 1,
          date: '2024-01-15',
          type: 'purchase',
          reference: 'PO-2024-001',
          description: 'Office supplies - January',
          amount: 1500,
          balance: 1500
        },
        {
          id: 2,
          date: '2024-01-20',
          type: 'payment',
          reference: 'CHK-001',
          description: 'Payment for PO-2024-001',
          amount: -1000,
          balance: 500
        },
        {
          id: 3,
          date: '2024-02-01',
          type: 'purchase',
          reference: 'PO-2024-002',
          description: 'Office supplies - February',
          amount: 2000,
          balance: 2500
        }
      ]
    },
    {
      id: 2,
      name: 'Tech Solutions Inc',
      contactPerson: 'Sarah Johnson',
      email: 'sarah@techsolutions.com',
      phone: '(555) 987-6543',
      address: '456 Technology Drive',
      city: 'Tech City',
      state: 'TC',
      zipCode: '67890',
      country: 'USA',
      taxId: '98-7654321',
      paymentTerms: 'Net 15',
      creditLimit: 25000,
      currentBalance: 8500,
      status: 'active',
      category: 'Technology',
      notes: 'IT equipment and software vendor',
      transactions: [
        {
          id: 1,
          date: '2024-01-10',
          type: 'purchase',
          reference: 'PO-2024-003',
          description: 'Laptops and accessories',
          amount: 12000,
          balance: 12000
        },
        {
          id: 2,
          date: '2024-01-25',
          type: 'payment',
          reference: 'CHK-002',
          description: 'Partial payment for laptops',
          amount: -3500,
          balance: 8500
        }
      ]
    },
    {
      id: 3,
      name: 'Marketing Materials Co',
      contactPerson: 'Mike Wilson',
      email: 'mike@marketingmaterials.com',
      phone: '(555) 456-7890',
      address: '789 Marketing Ave',
      city: 'Marketing City',
      state: 'MC',
      zipCode: '13579',
      country: 'USA',
      taxId: '45-6789012',
      paymentTerms: 'Net 30',
      creditLimit: 5000,
      currentBalance: 0,
      status: 'inactive',
      category: 'Marketing',
      notes: 'Printing and promotional materials',
      transactions: [
        {
          id: 1,
          date: '2023-12-15',
          type: 'purchase',
          reference: 'PO-2023-015',
          description: 'Business cards and brochures',
          amount: 800,
          balance: 800
        },
        {
          id: 2,
          date: '2024-01-15',
          type: 'payment',
          reference: 'CHK-003',
          description: 'Payment for business cards',
          amount: -800,
          balance: 0
        }
      ]
    }
  ];

  let showCreateForm = false;
  let selectedVendor: Vendor | null = null;
  let showVendorDetails = false;
  let searchTerm = '';
  let selectedStatus = 'all';
  let selectedCategory = 'all';

  // New vendor form data
  let newVendor = {
    name: '',
    contactPerson: '',
    email: '',
    phone: '',
    address: '',
    city: '',
    state: '',
    zipCode: '',
    country: 'USA',
    taxId: '',
    paymentTerms: 'Net 30',
    creditLimit: 0,
    category: '',
    notes: ''
  };

  // Filter vendors
  $: filteredVendors = vendors.filter(vendor => {
    const matchesSearch = vendor.name.toLowerCase().includes(searchTerm.toLowerCase()) ||
                         vendor.contactPerson.toLowerCase().includes(searchTerm.toLowerCase()) ||
                         vendor.email.toLowerCase().includes(searchTerm.toLowerCase());
    const matchesStatus = selectedStatus === 'all' || vendor.status === selectedStatus;
    const matchesCategory = selectedCategory === 'all' || vendor.category === selectedCategory;
    
    return matchesSearch && matchesStatus && matchesCategory;
  });

  // Get unique categories for filter
  $: categories = [...new Set(vendors.map(vendor => vendor.category))];

  function createVendor() {
    const vendor: Vendor = {
      id: Math.max(...vendors.map(v => v.id)) + 1,
      ...newVendor,
      currentBalance: 0,
      status: 'active',
      transactions: []
    };

    vendors = [...vendors, vendor];
    
    // Reset form
    newVendor = {
      name: '',
      contactPerson: '',
      email: '',
      phone: '',
      address: '',
      city: '',
      state: '',
      zipCode: '',
      country: 'USA',
      taxId: '',
      paymentTerms: 'Net 30',
      creditLimit: 0,
      category: '',
      notes: ''
    };
    
    showCreateForm = false;
  }

  function viewVendorDetails(vendor: Vendor) {
    selectedVendor = vendor;
    showVendorDetails = true;
  }

  function updateVendorStatus(vendorId: number, status: Vendor['status']) {
    vendors = vendors.map(vendor => 
      vendor.id === vendorId 
        ? { ...vendor, status }
        : vendor
    );
  }

  function deleteVendor(vendorId: number) {
    if (confirm('Are you sure you want to delete this vendor? This action cannot be undone.')) {
      vendors = vendors.filter(vendor => vendor.id !== vendorId);
    }
  }

  function getStatusColor(status: Vendor['status']): string {
    switch (status) {
      case 'active': return '#28a745';
      case 'inactive': return '#6c757d';
      case 'suspended': return '#dc3545';
      default: return '#6c757d';
    }
  }

  function getStatusLabel(status: Vendor['status']): string {
    switch (status) {
      case 'active': return 'Active';
      case 'inactive': return 'Inactive';
      case 'suspended': return 'Suspended';
      default: return status;
    }
  }

  function getTransactionTypeLabel(type: VendorTransaction['type']): string {
    switch (type) {
      case 'purchase': return 'Purchase';
      case 'payment': return 'Payment';
      case 'credit': return 'Credit';
      case 'refund': return 'Refund';
      default: return type;
    }
  }

  function getTransactionTypeColor(type: VendorTransaction['type']): string {
    switch (type) {
      case 'purchase': return '#dc3545';
      case 'payment': return '#28a745';
      case 'credit': return '#17a2b8';
      case 'refund': return '#ffc107';
      default: return '#6c757d';
    }
  }

  // Calculate summary statistics
  $: totalVendors = vendors.length;
  $: activeVendors = vendors.filter(v => v.status === 'active').length;
  $: totalBalance = vendors.reduce((sum, vendor) => sum + vendor.currentBalance, 0);
  $: averageCreditLimit = vendors.length > 0 
    ? vendors.reduce((sum, vendor) => sum + vendor.creditLimit, 0) / vendors.length 
    : 0;
</script>

<RoleGuard resource="vendors" action="read" fallback="You need permission to access vendors.">
  <section class="vendors">
    <div class="vendors-header">
      <h1>Vendors and Suppliers</h1>
      <p>Manage vendor relationships, supplier information, and procurement data</p>
    </div>

    <div class="vendors-summary">
      <div class="summary-card">
        <h3>Total Vendors</h3>
        <p class="amount">{totalVendors}</p>
      </div>
      <div class="summary-card">
        <h3>Active Vendors</h3>
        <p class="amount">{activeVendors}</p>
      </div>
      <div class="summary-card">
        <h3>Total Balance</h3>
        <p class="amount">${totalBalance.toLocaleString()}</p>
      </div>
      <div class="summary-card">
        <h3>Avg Credit Limit</h3>
        <p class="amount">${averageCreditLimit.toLocaleString()}</p>
      </div>
    </div>

    <div class="vendors-controls">
      <div class="search-filters">
        <div class="search-box">
          <input 
            type="text" 
            placeholder="Search vendors..." 
            bind:value={searchTerm}
          />
        </div>
        
        <div class="filters">
          <select bind:value={selectedStatus}>
            <option value="all">All Status</option>
            <option value="active">Active</option>
            <option value="inactive">Inactive</option>
            <option value="suspended">Suspended</option>
          </select>
          
          <select bind:value={selectedCategory}>
            <option value="all">All Categories</option>
            {#each categories as category}
              <option value={category}>{category}</option>
            {/each}
          </select>
        </div>
      </div>

      <button class="create-btn" on:click={() => showCreateForm = true}>
        Add Vendor
      </button>
    </div>

    {#if showCreateForm}
      <div class="create-vendor-form">
        <div class="form-header">
          <h3>Add New Vendor</h3>
          <button class="close-btn" on:click={() => showCreateForm = false}>×</button>
        </div>
        
        <form on:submit|preventDefault={createVendor}>
          <div class="form-grid">
            <div class="form-group">
              <label for="vendor-name">Vendor Name *</label>
              <input 
                id="vendor-name"
                type="text" 
                bind:value={newVendor.name} 
                required
                placeholder="Enter vendor name"
              />
            </div>
            
            <div class="form-group">
              <label for="contact-person">Contact Person</label>
              <input 
                id="contact-person"
                type="text" 
                bind:value={newVendor.contactPerson} 
                placeholder="Contact person name"
              />
            </div>
            
            <div class="form-group">
              <label for="email">Email</label>
              <input 
                id="email"
                type="email" 
                bind:value={newVendor.email} 
                placeholder="vendor@example.com"
              />
            </div>
            
            <div class="form-group">
              <label for="phone">Phone</label>
              <input 
                id="phone"
                type="tel" 
                bind:value={newVendor.phone} 
                placeholder="(555) 123-4567"
              />
            </div>
            
            <div class="form-group">
              <label for="category">Category</label>
              <input 
                id="category"
                type="text" 
                bind:value={newVendor.category} 
                placeholder="e.g., Office Supplies, Technology"
              />
            </div>
            
            <div class="form-group">
              <label for="tax-id">Tax ID</label>
              <input 
                id="tax-id"
                type="text" 
                bind:value={newVendor.taxId} 
                placeholder="XX-XXXXXXX"
              />
            </div>
            
            <div class="form-group">
              <label for="payment-terms">Payment Terms</label>
              <select id="payment-terms" bind:value={newVendor.paymentTerms}>
                <option value="Net 15">Net 15</option>
                <option value="Net 30">Net 30</option>
                <option value="Net 45">Net 45</option>
                <option value="Net 60">Net 60</option>
                <option value="Due on Receipt">Due on Receipt</option>
              </select>
            </div>
            
            <div class="form-group">
              <label for="credit-limit">Credit Limit ($)</label>
              <input 
                id="credit-limit"
                type="number" 
                bind:value={newVendor.creditLimit} 
                min="0"
                step="100"
                placeholder="10000"
              />
            </div>
            
            <div class="form-group">
              <label for="address">Address</label>
              <input 
                id="address"
                type="text" 
                bind:value={newVendor.address} 
                placeholder="Street address"
              />
            </div>
            
            <div class="form-group">
              <label for="city">City</label>
              <input 
                id="city"
                type="text" 
                bind:value={newVendor.city} 
                placeholder="City"
              />
            </div>
            
            <div class="form-group">
              <label for="state">State</label>
              <input 
                id="state"
                type="text" 
                bind:value={newVendor.state} 
                placeholder="State"
              />
            </div>
            
            <div class="form-group">
              <label for="zip-code">ZIP Code</label>
              <input 
                id="zip-code"
                type="text" 
                bind:value={newVendor.zipCode} 
                placeholder="12345"
              />
            </div>
            
            <div class="form-group">
              <label for="country">Country</label>
              <select id="country" bind:value={newVendor.country}>
                <option value="USA">United States</option>
                <option value="Canada">Canada</option>
                <option value="Mexico">Mexico</option>
                <option value="Other">Other</option>
              </select>
            </div>
            
            <div class="form-group full-width">
              <label for="notes">Notes</label>
              <textarea 
                id="notes"
                bind:value={newVendor.notes} 
                placeholder="Additional notes about this vendor"
                rows="3"
              ></textarea>
            </div>
          </div>
          
          <div class="form-actions">
            <button type="button" class="cancel-btn" on:click={() => showCreateForm = false}>
              Cancel
            </button>
            <button type="submit" class="save-btn">
              Add Vendor
            </button>
          </div>
        </form>
      </div>
    {/if}

    <div class="vendors-list">
      {#if filteredVendors.length === 0}
        <div class="empty-state">
          <h3>No vendors found</h3>
          <p>Try adjusting your search criteria or add a new vendor.</p>
        </div>
      {:else}
        <div class="vendors-grid">
          {#each filteredVendors as vendor}
            <div class="vendor-card">
              <div class="vendor-header">
                <h3>{vendor.name}</h3>
                <div class="vendor-badges">
                  <span class="badge status" style="background-color: {getStatusColor(vendor.status)}">
                    {getStatusLabel(vendor.status)}
                  </span>
                  <span class="badge category">{vendor.category}</span>
                </div>
              </div>
              
              <div class="vendor-details">
                {#if vendor.contactPerson}
                  <div class="detail">
                    <span class="label">Contact:</span>
                    <span class="value">{vendor.contactPerson}</span>
                  </div>
                {/if}
                
                {#if vendor.email}
                  <div class="detail">
                    <span class="label">Email:</span>
                    <span class="value">{vendor.email}</span>
                  </div>
                {/if}
                
                {#if vendor.phone}
                  <div class="detail">
                    <span class="label">Phone:</span>
                    <span class="value">{vendor.phone}</span>
                  </div>
                {/if}
                
                <div class="detail">
                  <span class="label">Balance:</span>
                  <span class="value" class:negative={vendor.currentBalance > 0}>
                    ${vendor.currentBalance.toLocaleString()}
                  </span>
                </div>
                
                <div class="detail">
                  <span class="label">Credit Limit:</span>
                  <span class="value">${vendor.creditLimit.toLocaleString()}</span>
                </div>
                
                <div class="detail">
                  <span class="label">Payment Terms:</span>
                  <span class="value">{vendor.paymentTerms}</span>
                </div>
              </div>
              
              <div class="vendor-actions">
                <button 
                  class="action-btn view" 
                  on:click={() => viewVendorDetails(vendor)}
                >
                  View Details
                </button>
                
                <select 
                  class="status-select" 
                  value={vendor.status}
                  on:change={(e) => updateVendorStatus(vendor.id, e.target.value as Vendor['status'])}
                >
                  <option value="active">Active</option>
                  <option value="inactive">Inactive</option>
                  <option value="suspended">Suspended</option>
                </select>
                
                <button 
                  class="action-btn delete" 
                  on:click={() => deleteVendor(vendor.id)}
                >
                  Delete
                </button>
              </div>
            </div>
          {/each}
        </div>
      {/if}
    </div>

    {#if showVendorDetails && selectedVendor}
      <div class="vendor-details-modal">
        <div class="modal-content">
          <div class="modal-header">
            <h2>{selectedVendor.name}</h2>
            <button class="close-btn" on:click={() => showVendorDetails = false}>×</button>
          </div>
          
          <div class="vendor-info">
            <div class="info-section">
              <h3>Contact Information</h3>
              <div class="info-grid">
                {#if selectedVendor.contactPerson}
                  <div class="info-item">
                    <span class="label">Contact Person:</span>
                    <span class="value">{selectedVendor.contactPerson}</span>
                  </div>
                {/if}
                
                {#if selectedVendor.email}
                  <div class="info-item">
                    <span class="label">Email:</span>
                    <span class="value">{selectedVendor.email}</span>
                  </div>
                {/if}
                
                {#if selectedVendor.phone}
                  <div class="info-item">
                    <span class="label">Phone:</span>
                    <span class="value">{selectedVendor.phone}</span>
                  </div>
                {/if}
                
                {#if selectedVendor.address}
                  <div class="info-item full-width">
                    <span class="label">Address:</span>
                    <span class="value">
                      {selectedVendor.address}<br>
                      {selectedVendor.city}, {selectedVendor.state} {selectedVendor.zipCode}<br>
                      {selectedVendor.country}
                    </span>
                  </div>
                {/if}
              </div>
            </div>
            
            <div class="info-section">
              <h3>Financial Information</h3>
              <div class="info-grid">
                <div class="info-item">
                  <span class="label">Current Balance:</span>
                  <span class="value" class:negative={selectedVendor.currentBalance > 0}>
                    ${selectedVendor.currentBalance.toLocaleString()}
                  </span>
                </div>
                
                <div class="info-item">
                  <span class="label">Credit Limit:</span>
                  <span class="value">${selectedVendor.creditLimit.toLocaleString()}</span>
                </div>
                
                <div class="info-item">
                  <span class="label">Payment Terms:</span>
                  <span class="value">{selectedVendor.paymentTerms}</span>
                </div>
                
                {#if selectedVendor.taxId}
                  <div class="info-item">
                    <span class="label">Tax ID:</span>
                    <span class="value">{selectedVendor.taxId}</span>
                  </div>
                {/if}
              </div>
            </div>
            
            {#if selectedVendor.notes}
              <div class="info-section">
                <h3>Notes</h3>
                <p>{selectedVendor.notes}</p>
              </div>
            {/if}
            
            <div class="info-section">
              <h3>Transaction History</h3>
              {#if selectedVendor.transactions.length === 0}
                <p class="no-transactions">No transactions found for this vendor.</p>
              {:else}
                <div class="transactions-table">
                  <table>
                    <thead>
                      <tr>
                        <th>Date</th>
                        <th>Type</th>
                        <th>Reference</th>
                        <th>Description</th>
                        <th>Amount</th>
                        <th>Balance</th>
                      </tr>
                    </thead>
                    <tbody>
                      {#each selectedVendor.transactions.sort((a, b) => new Date(b.date).getTime() - new Date(a.date).getTime()) as transaction}
                        <tr>
                          <td>{new Date(transaction.date).toLocaleDateString()}</td>
                          <td>
                            <span class="transaction-type" style="background-color: {getTransactionTypeColor(transaction.type)}">
                              {getTransactionTypeLabel(transaction.type)}
                            </span>
                          </td>
                          <td>{transaction.reference}</td>
                          <td>{transaction.description}</td>
                          <td class:negative={transaction.amount < 0}>
                            ${transaction.amount.toFixed(2)}
                          </td>
                          <td>${transaction.balance.toFixed(2)}</td>
                        </tr>
                      {/each}
                    </tbody>
                  </table>
                </div>
              {/if}
            </div>
          </div>
          
          <div class="modal-actions">
            <button class="close-modal-btn" on:click={() => showVendorDetails = false}>Close</button>
          </div>
        </div>
      </div>
    {/if}
  </section>
</RoleGuard>

<style>
  .vendors {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .vendors-header {
    text-align: center;
    margin-bottom: 2rem;
  }

  .vendors-header h1 {
    font-size: 2rem;
    margin-bottom: 0.5rem;
    color: #333;
  }

  .vendors-header p {
    color: #666;
    font-size: 1.1rem;
  }

  .vendors-summary {
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

  .vendors-controls {
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

  .create-vendor-form {
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

  .vendors-list {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
  }

  .vendors-grid {
    display: grid;
    gap: 1rem;
  }

  .vendor-card {
    border: 1px solid #e9ecef;
    border-radius: 8px;
    padding: 1.5rem;
    transition: all 0.2s;
  }

  .vendor-card:hover {
    box-shadow: 0 4px 12px rgba(0,0,0,0.1);
  }

  .vendor-header {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    margin-bottom: 1rem;
  }

  .vendor-header h3 {
    margin: 0;
    color: #333;
    font-size: 1.1rem;
  }

  .vendor-badges {
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

  .badge.status {
    color: white;
  }

  .badge.category {
    background: #17a2b8;
    color: white;
  }

  .vendor-details {
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

  .detail .value.negative {
    color: #dc3545;
  }

  .vendor-actions {
    display: flex;
    gap: 0.5rem;
    align-items: center;
  }

  .action-btn {
    padding: 0.5rem 1rem;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .action-btn.view {
    background: #17a2b8;
    color: white;
  }

  .action-btn.view:hover {
    background: #138496;
  }

  .action-btn.delete {
    background: #dc3545;
    color: white;
  }

  .action-btn.delete:hover {
    background: #c82333;
  }

  .status-select {
    padding: 0.5rem;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 0.875rem;
  }

  .empty-state {
    text-align: center;
    padding: 3rem;
    color: #666;
  }

  .empty-state h3 {
    margin-bottom: 0.5rem;
  }

  /* Vendor Details Modal */
  .vendor-details-modal {
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
    max-width: 900px;
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

  .vendor-info {
    padding: 1.5rem;
  }

  .info-section {
    margin-bottom: 2rem;
  }

  .info-section h3 {
    margin: 0 0 1rem 0;
    color: #333;
    font-size: 1.1rem;
  }

  .info-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
  }

  .info-item {
    display: flex;
    flex-direction: column;
    gap: 0.25rem;
  }

  .info-item.full-width {
    grid-column: 1 / -1;
  }

  .info-item .label {
    font-weight: 500;
    color: #666;
    font-size: 0.875rem;
  }

  .info-item .value {
    color: #333;
  }

  .info-item .value.negative {
    color: #dc3545;
  }

  .no-transactions {
    color: #666;
    font-style: italic;
  }

  .transactions-table {
    overflow-x: auto;
  }

  .transactions-table table {
    width: 100%;
    border-collapse: collapse;
  }

  .transactions-table th,
  .transactions-table td {
    padding: 0.75rem;
    text-align: left;
    border-bottom: 1px solid #e9ecef;
  }

  .transactions-table th {
    background: #f8f9fa;
    font-weight: 600;
    color: #333;
  }

  .transactions-table tr:hover {
    background: #f8f9fa;
  }

  .transaction-type {
    padding: 0.25rem 0.5rem;
    border-radius: 4px;
    color: white;
    font-size: 0.75rem;
    font-weight: 500;
  }

  .transactions-table td.negative {
    color: #dc3545;
  }

  .modal-actions {
    display: flex;
    gap: 1rem;
    justify-content: flex-end;
    padding: 1.5rem;
    border-top: 1px solid #e9ecef;
  }

  .close-modal-btn {
    padding: 0.75rem 1.5rem;
    background: #6c757d;
    color: white;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .close-modal-btn:hover {
    background: #545b62;
  }

  @media (max-width: 768px) {
    .vendors-controls {
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

    .vendor-header {
      flex-direction: column;
      align-items: flex-start;
      gap: 0.5rem;
    }

    .vendor-actions {
      flex-direction: column;
      gap: 0.5rem;
    }

    .action-btn {
      width: 100%;
    }

    .modal-content {
      width: 95%;
      margin: 1rem;
    }

    .info-grid {
      grid-template-columns: 1fr;
    }
  }
</style> 