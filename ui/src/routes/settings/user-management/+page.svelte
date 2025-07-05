<script>
  import { auth } from '$lib/auth';
  import { ROLE_PERMISSIONS, hasPermission } from '$lib/roles';
  import RoleGuard from '$lib/RoleGuard.svelte';

  // Mock user data - in real app, this would come from an API
  let users = [
    { id: 1, email: 'admin@pentaledger.com', name: 'Admin User', role: 'admin', status: 'active' },
    { id: 2, email: 'manager@pentaledger.com', name: 'Manager User', role: 'manager', status: 'active' },
    { id: 3, email: 'accountant@pentaledger.com', name: 'Accountant User', role: 'accountant', status: 'active' },
    { id: 4, email: 'user@pentaledger.com', name: 'Regular User', role: 'user', status: 'active' },
    { id: 5, email: 'john.doe@company.com', name: 'John Doe', role: 'user', status: 'inactive' },
    { id: 6, email: 'jane.smith@company.com', name: 'Jane Smith', role: 'accountant', status: 'active' }
  ];

  let editingUser = null;
  let showAddUser = false;
  let newUser = {
    email: '',
    name: '',
    role: 'user',
    status: 'active'
  };

  const roles = ['admin', 'manager', 'accountant', 'user'];

  function editUser(user) {
    editingUser = { ...user };
  }

  function saveUser() {
    if (editingUser) {
      const index = users.findIndex(u => u.id === editingUser.id);
      if (index !== -1) {
        users[index] = { ...editingUser };
        users = [...users]; // Trigger reactivity
      }
      editingUser = null;
    }
  }

  function cancelEdit() {
    editingUser = null;
  }

  function addUser() {
    if (newUser.email && newUser.name) {
      const user = {
        id: Date.now(), // Simple ID generation
        ...newUser
      };
      users = [...users, user];
      newUser = { email: '', name: '', role: 'user', status: 'active' };
      showAddUser = false;
    }
  }

  function deleteUser(userId) {
    if (confirm('Are you sure you want to delete this user?')) {
      users = users.filter(u => u.id !== userId);
    }
  }

  function toggleUserStatus(user) {
    user.status = user.status === 'active' ? 'inactive' : 'active';
    users = [...users]; // Trigger reactivity
  }
</script>

<RoleGuard resource="user-management" action="read" fallback="You need admin permissions to access user management.">
  <section class="user-management">
    <div class="header">
      <h1>User Management</h1>
      <button class="add-user-btn" on:click={() => showAddUser = true}>
        Add New User
      </button>
    </div>

    {#if showAddUser}
      <div class="add-user-form">
        <h3>Add New User</h3>
        <div class="form-row">
          <div class="form-group">
            <label for="new-email">Email</label>
            <input 
              type="email" 
              id="new-email" 
              bind:value={newUser.email} 
              placeholder="Enter email"
            />
          </div>
          <div class="form-group">
            <label for="new-name">Name</label>
            <input 
              type="text" 
              id="new-name" 
              bind:value={newUser.name} 
              placeholder="Enter name"
            />
          </div>
          <div class="form-group">
            <label for="new-role">Role</label>
            <select id="new-role" bind:value={newUser.role}>
              {#each roles as role}
                <option value={role}>{role}</option>
              {/each}
            </select>
          </div>
        </div>
        <div class="form-actions">
          <button class="save-btn" on:click={addUser}>Add User</button>
          <button class="cancel-btn" on:click={() => showAddUser = false}>Cancel</button>
        </div>
      </div>
    {/if}

    <div class="users-table">
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Email</th>
            <th>Role</th>
            <th>Status</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {#each users as user}
            <tr class={user.status === 'inactive' ? 'inactive' : ''}>
              <td>
                {#if editingUser && editingUser.id === user.id}
                  <input type="text" bind:value={editingUser.name} />
                {:else}
                  {user.name}
                {/if}
              </td>
              <td>
                {#if editingUser && editingUser.id === user.id}
                  <input type="email" bind:value={editingUser.email} />
                {:else}
                  {user.email}
                {/if}
              </td>
              <td>
                {#if editingUser && editingUser.id === user.id}
                  <select bind:value={editingUser.role}>
                    {#each roles as role}
                      <option value={role}>{role}</option>
                    {/each}
                  </select>
                {:else}
                  <span class="role-badge {user.role}">{user.role}</span>
                {/if}
              </td>
              <td>
                <span class="status-badge {user.status}">{user.status}</span>
              </td>
              <td class="actions">
                {#if editingUser && editingUser.id === user.id}
                  <button class="save-btn" on:click={saveUser}>Save</button>
                  <button class="cancel-btn" on:click={cancelEdit}>Cancel</button>
                {:else}
                  <button class="edit-btn" on:click={() => editUser(user)}>Edit</button>
                  <button class="status-btn" on:click={() => toggleUserStatus(user)}>
                    {user.status === 'active' ? 'Deactivate' : 'Activate'}
                  </button>
                  <button class="delete-btn" on:click={() => deleteUser(user.id)}>Delete</button>
                {/if}
              </td>
            </tr>
          {/each}
        </tbody>
      </table>
    </div>

    <div class="permissions-overview">
      <h2>Role Permissions Overview</h2>
      <div class="permissions-grid">
        {#each roles as role}
          <div class="role-permissions">
            <h3>{role}</h3>
            <ul>
              {#each ROLE_PERMISSIONS[role] as permission}
                <li>
                  <strong>{permission.resource}:</strong> {permission.actions.join(', ')}
                </li>
              {/each}
            </ul>
          </div>
        {/each}
      </div>
    </div>
  </section>
</RoleGuard>

<style>
  .user-management {
    max-width: 1200px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 2rem;
  }

  .header h1 {
    font-size: 2rem;
    margin: 0;
  }

  .add-user-btn {
    background: #28a745;
    color: white;
    border: none;
    padding: 0.75rem 1.5rem;
    border-radius: 6px;
    cursor: pointer;
    font-size: 1rem;
  }

  .add-user-btn:hover {
    background: #218838;
  }

  .add-user-form {
    background: #f8f9fa;
    padding: 1.5rem;
    border-radius: 8px;
    margin-bottom: 2rem;
  }

  .add-user-form h3 {
    margin-top: 0;
    margin-bottom: 1rem;
  }

  .form-row {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr;
    gap: 1rem;
    margin-bottom: 1rem;
  }

  .form-group {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }

  .form-group label {
    font-weight: 500;
    color: #333;
  }

  .form-group input,
  .form-group select {
    padding: 0.5rem;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 1rem;
  }

  .form-actions {
    display: flex;
    gap: 1rem;
  }

  .users-table {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    overflow: hidden;
    margin-bottom: 2rem;
  }

  table {
    width: 100%;
    border-collapse: collapse;
  }

  th {
    background: #f8f9fa;
    padding: 1rem;
    text-align: left;
    font-weight: 600;
    color: #333;
    border-bottom: 1px solid #dee2e6;
  }

  td {
    padding: 1rem;
    border-bottom: 1px solid #dee2e6;
  }

  tr:last-child td {
    border-bottom: none;
  }

  tr.inactive {
    opacity: 0.6;
  }

  .role-badge {
    padding: 0.25rem 0.75rem;
    border-radius: 20px;
    font-size: 0.875rem;
    font-weight: 500;
  }

  .role-badge.admin {
    background: #dc3545;
    color: white;
  }

  .role-badge.manager {
    background: #fd7e14;
    color: white;
  }

  .role-badge.accountant {
    background: #6f42c1;
    color: white;
  }

  .role-badge.user {
    background: #6c757d;
    color: white;
  }

  .status-badge {
    padding: 0.25rem 0.75rem;
    border-radius: 20px;
    font-size: 0.875rem;
    font-weight: 500;
  }

  .status-badge.active {
    background: #28a745;
    color: white;
  }

  .status-badge.inactive {
    background: #6c757d;
    color: white;
  }

  .actions {
    display: flex;
    gap: 0.5rem;
  }

  .edit-btn,
  .save-btn {
    background: #007bff;
    color: white;
    border: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
  }

  .edit-btn:hover,
  .save-btn:hover {
    background: #0056b3;
  }

  .status-btn {
    background: #ffc107;
    color: #212529;
    border: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
  }

  .status-btn:hover {
    background: #e0a800;
  }

  .delete-btn {
    background: #dc3545;
    color: white;
    border: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
  }

  .delete-btn:hover {
    background: #c82333;
  }

  .cancel-btn {
    background: #6c757d;
    color: white;
    border: none;
    padding: 0.5rem 1rem;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.875rem;
  }

  .cancel-btn:hover {
    background: #545b62;
  }

  .permissions-overview {
    background: white;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    padding: 2rem;
  }

  .permissions-overview h2 {
    margin-top: 0;
    margin-bottom: 1.5rem;
  }

  .permissions-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 1.5rem;
  }

  .role-permissions {
    background: #f8f9fa;
    padding: 1.5rem;
    border-radius: 6px;
  }

  .role-permissions h3 {
    margin-top: 0;
    margin-bottom: 1rem;
    color: #333;
  }

  .role-permissions ul {
    list-style: none;
    padding: 0;
    margin: 0;
  }

  .role-permissions li {
    padding: 0.5rem 0;
    border-bottom: 1px solid #dee2e6;
    font-size: 0.9rem;
  }

  .role-permissions li:last-child {
    border-bottom: none;
  }
</style> 