<script lang="ts">
  import { auth } from '$lib/auth';
  import RoleGuard from '$lib/RoleGuard.svelte';

  // Sample companies data
  let companies = [
    {
      id: 1,
      name: 'Acme Corporation',
      type: 'Corporation',
      taxId: '12-3456789',
      address: '123 Business St, City, State 12345',
      phone: '(555) 123-4567',
      email: 'contact@acme.com',
      website: 'www.acme.com',
      fiscalYearEnd: '12/31',
      isActive: true,
      isCurrent: true
    },
    {
      id: 2,
      name: 'TechStart LLC',
      type: 'LLC',
      taxId: '98-7654321',
      address: '456 Innovation Ave, Tech City, TC 67890',
      phone: '(555) 987-6543',
      email: 'hello@techstart.com',
      website: 'www.techstart.com',
      fiscalYearEnd: '12/31',
      isActive: true,
      isCurrent: false
    },
    {
      id: 3,
      name: 'Global Manufacturing Inc',
      type: 'Corporation',
      taxId: '45-6789012',
      address: '789 Industrial Blvd, Factory Town, FT 13579',
      phone: '(555) 456-7890',
      email: 'info@globalmfg.com',
      website: 'www.globalmfg.com',
      fiscalYearEnd: '06/30',
      isActive: true,
      isCurrent: false
    },
    {
      id: 4,
      name: 'Retired Ventures',
      type: 'Partnership',
      taxId: '34-5678901',
      address: '321 Sunset Dr, Retirement City, RC 24680',
      phone: '(555) 345-6789',
      email: 'contact@retiredventures.com',
      website: 'www.retiredventures.com',
      fiscalYearEnd: '12/31',
      isActive: false,
      isCurrent: false
    }
  ];

  let showAddForm = false;
  let searchTerm = '';
  let selectedCompanyType = 'all';
  let selectedStatus = 'all';

  // New company form data
  let newCompany = {
    name: '',
    type: 'Corporation',
    taxId: '',
    address: '',
    phone: '',
    email: '',
    website: '',
    fiscalYearEnd: '12/31'
  };

  // Filter companies based on search and filters
  $: filteredCompanies = companies.filter(company => {
    const matchesSearch = company.name.toLowerCase().includes(searchTerm.toLowerCase()) ||
                         company.taxId.includes(searchTerm) ||
                         company.email.toLowerCase().includes(searchTerm.toLowerCase());
    const matchesType = selectedCompanyType === 'all' || company.type === selectedCompanyType;
    const matchesStatus = selectedStatus === 'all' || 
                         (selectedStatus === 'active' && company.isActive) ||
                         (selectedStatus === 'inactive' && !company.isActive);
    
    return matchesSearch && matchesType && matchesStatus;
  });

  function setCurrentCompany(companyId: number) {
    companies = companies.map(company => ({
      ...company,
      isCurrent: company.id === companyId
    }));
  }

  function addCompany() {
    const company = {
      id: Math.max(...companies.map(c => c.id)) + 1,
      ...newCompany,
      isActive: true,
      isCurrent: false
    };
    
    companies = [...companies, company];
    
    // Reset form
    newCompany = {
      name: '',
      type: 'Corporation',
      taxId: '',
      address: '',
      phone: '',
      email: '',
      website: '',
      fiscalYearEnd: '12/31'
    };
    
    showAddForm = false;
  }

  function toggleCompanyStatus(companyId: number) {
    companies = companies.map(company => 
      company.id === companyId 
        ? { ...company, isActive: !company.isActive }
        : company
    );
  }

  function deleteCompany(companyId: number) {
    if (confirm('Are you sure you want to delete this company? This action cannot be undone.')) {
      companies = companies.filter(company => company.id !== companyId);
    }
  }
</script>

<RoleGuard resource="companies" action="read" fallback="You need permission to access companies.">
  <section class="companies">
    <div class="companies-header">
      <h1>Companies</h1>
      <p>Manage companies in your accounting system</p>
    </div>

    <div class="companies-controls">
      <div class="search-filters">
        <div class="search-box">
          <input 
            type="text" 
            placeholder="Search companies..." 
            bind:value={searchTerm}
          />
        </div>
        
        <div class="filters">
          <select bind:value={selectedCompanyType}>
            <option value="all">All Types</option>
            <option value="Corporation">Corporation</option>
            <option value="LLC">LLC</option>
            <option value="Partnership">Partnership</option>
            <option value="Sole Proprietorship">Sole Proprietorship</option>
          </select>
          
          <select bind:value={selectedStatus}>
            <option value="all">All Status</option>
            <option value="active">Active</option>
            <option value="inactive">Inactive</option>
          </select>
        </div>
      </div>

      <button class="add-btn" on:click={() => showAddForm = true}>
        Add Company
      </button>
    </div>

    {#if showAddForm}
      <div class="add-company-form">
        <div class="form-header">
          <h3>Add New Company</h3>
          <button class="close-btn" on:click={() => showAddForm = false}>×</button>
        </div>
        
        <form on:submit|preventDefault={addCompany}>
          <div class="form-grid">
            <div class="form-group">
              <label for="company-name">Company Name *</label>
              <input 
                id="company-name"
                type="text" 
                bind:value={newCompany.name} 
                required
                placeholder="Enter company name"
              />
            </div>
            
            <div class="form-group">
              <label for="company-type">Company Type *</label>
              <select id="company-type" bind:value={newCompany.type} required>
                <option value="Corporation">Corporation</option>
                <option value="LLC">LLC</option>
                <option value="Partnership">Partnership</option>
                <option value="Sole Proprietorship">Sole Proprietorship</option>
              </select>
            </div>
            
            <div class="form-group">
              <label for="tax-id">Tax ID</label>
              <input 
                id="tax-id"
                type="text" 
                bind:value={newCompany.taxId} 
                placeholder="XX-XXXXXXX"
              />
            </div>
            
            <div class="form-group">
              <label for="fiscal-year">Fiscal Year End</label>
              <select id="fiscal-year" bind:value={newCompany.fiscalYearEnd}>
                <option value="12/31">December 31</option>
                <option value="06/30">June 30</option>
                <option value="03/31">March 31</option>
                <option value="09/30">September 30</option>
              </select>
            </div>
            
            <div class="form-group full-width">
              <label for="address">Address</label>
              <textarea 
                id="address"
                bind:value={newCompany.address} 
                placeholder="Enter full address"
                rows="3"
              ></textarea>
            </div>
            
            <div class="form-group">
              <label for="phone">Phone</label>
              <input 
                id="phone"
                type="tel" 
                bind:value={newCompany.phone} 
                placeholder="(555) 123-4567"
              />
            </div>
            
            <div class="form-group">
              <label for="email">Email</label>
              <input 
                id="email"
                type="email" 
                bind:value={newCompany.email} 
                placeholder="contact@company.com"
              />
            </div>
            
            <div class="form-group">
              <label for="website">Website</label>
              <input 
                id="website"
                type="url" 
                bind:value={newCompany.website} 
                placeholder="www.company.com"
              />
            </div>
          </div>
          
          <div class="form-actions">
            <button type="button" class="cancel-btn" on:click={() => showAddForm = false}>
              Cancel
            </button>
            <button type="submit" class="save-btn">
              Add Company
            </button>
          </div>
        </form>
      </div>
    {/if}

    <div class="companies-list">
      {#if filteredCompanies.length === 0}
        <div class="empty-state">
          <h3>No companies found</h3>
          <p>Try adjusting your search criteria or add a new company.</p>
        </div>
      {:else}
        {#each filteredCompanies as company}
          <div class="company-card" class:current={company.isCurrent} class:inactive={!company.isActive}>
            <div class="company-info">
              <div class="company-header">
                <h3>{company.name}</h3>
                <div class="company-badges">
                  {#if company.isCurrent}
                    <span class="badge current">Current</span>
                  {/if}
                  <span class="badge type">{company.type}</span>
                  <span class="badge status" class:active={company.isActive}>
                    {company.isActive ? 'Active' : 'Inactive'}
                  </span>
                </div>
              </div>
              
              <div class="company-details">
                {#if company.taxId}
                  <div class="detail">
                    <span class="label">Tax ID:</span>
                    <span class="value">{company.taxId}</span>
                  </div>
                {/if}
                
                {#if company.email}
                  <div class="detail">
                    <span class="label">Email:</span>
                    <span class="value">{company.email}</span>
                  </div>
                {/if}
                
                {#if company.phone}
                  <div class="detail">
                    <span class="label">Phone:</span>
                    <span class="value">{company.phone}</span>
                  </div>
                {/if}
                
                {#if company.website}
                  <div class="detail">
                    <span class="label">Website:</span>
                    <span class="value">{company.website}</span>
                  </div>
                {/if}
                
                <div class="detail">
                  <span class="label">Fiscal Year End:</span>
                  <span class="value">{company.fiscalYearEnd}</span>
                </div>
              </div>
            </div>
            
            <div class="company-actions">
              {#if !company.isCurrent}
                <button 
                  class="action-btn set-current" 
                  on:click={() => setCurrentCompany(company.id)}
                >
                  Set as Current
                </button>
              {/if}
              
              <button 
                class="action-btn toggle-status" 
                on:click={() => toggleCompanyStatus(company.id)}
              >
                {company.isActive ? 'Deactivate' : 'Activate'}
              </button>
              
              <button 
                class="action-btn delete" 
                on:click={() => deleteCompany(company.id)}
              >
                Delete
              </button>
            </div>
          </div>
        {/each}
      {/if}
    </div>
  </section>
</RoleGuard>

<style>
  .companies {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .companies-header {
    text-align: center;
    margin-bottom: 2rem;
  }

  .companies-header h1 {
    font-size: 2rem;
    margin-bottom: 0.5rem;
    color: #333;
  }

  .companies-header p {
    color: #666;
    font-size: 1.1rem;
  }

  .companies-controls {
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

  .add-btn {
    padding: 0.75rem 1.5rem;
    background: #28a745;
    color: white;
    border: none;
    border-radius: 6px;
    cursor: pointer;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .add-btn:hover {
    background: #218838;
  }

  .add-company-form {
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

  .companies-list {
    display: grid;
    gap: 1rem;
  }

  .company-card {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 1.5rem;
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    gap: 1rem;
    transition: all 0.2s;
  }

  .company-card:hover {
    box-shadow: 0 4px 12px rgba(0,0,0,0.15);
  }

  .company-card.current {
    border: 2px solid #28a745;
  }

  .company-card.inactive {
    opacity: 0.7;
  }

  .company-info {
    flex: 1;
  }

  .company-header {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    margin-bottom: 1rem;
  }

  .company-header h3 {
    margin: 0;
    color: #333;
    font-size: 1.2rem;
  }

  .company-badges {
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

  .badge.current {
    background: #28a745;
    color: white;
  }

  .badge.type {
    background: #17a2b8;
    color: white;
  }

  .badge.status {
    background: #6c757d;
    color: white;
  }

  .badge.status.active {
    background: #28a745;
  }

  .company-details {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 0.5rem;
  }

  .detail {
    display: flex;
    gap: 0.5rem;
  }

  .detail .label {
    font-weight: 500;
    color: #666;
    min-width: 80px;
  }

  .detail .value {
    color: #333;
  }

  .company-actions {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
    min-width: 120px;
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

  .action-btn.set-current {
    background: #28a745;
    color: white;
  }

  .action-btn.set-current:hover {
    background: #218838;
  }

  .action-btn.toggle-status {
    background: #ffc107;
    color: #212529;
  }

  .action-btn.toggle-status:hover {
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
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
  }

  .empty-state h3 {
    color: #333;
    margin-bottom: 0.5rem;
  }

  .empty-state p {
    color: #666;
  }

  @media (max-width: 768px) {
    .companies-controls {
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

    .company-card {
      flex-direction: column;
    }

    .company-header {
      flex-direction: column;
      align-items: flex-start;
      gap: 0.5rem;
    }

    .company-actions {
      flex-direction: row;
      justify-content: stretch;
    }

    .action-btn {
      flex: 1;
    }
  }
</style> 