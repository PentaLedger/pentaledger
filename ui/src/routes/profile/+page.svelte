<script>
  import { auth } from '$lib/auth';
  import RoleGuard from '$lib/RoleGuard.svelte';

  let isEditing = false;
  let profileData = {
    name: '',
    email: '',
    phone: '',
    department: '',
    title: '',
    bio: ''
  };

  // Initialize profile data from auth store
  $: if ($auth.user && !isEditing) {
    profileData = {
      name: $auth.user.name || '',
      email: $auth.user.email || '',
      phone: '',
      department: '',
      title: '',
      bio: ''
    };
  }

  function startEditing() {
    isEditing = true;
  }

  function saveProfile() {
    // In a real app, this would make an API call to update the user profile
    console.log('Saving profile:', profileData);
    
    // Update the auth store with new name
    if ($auth.user) {
      auth.update(state => ({
        ...state,
        user: {
          ...state.user,
          name: profileData.name
        }
      }));
    }
    
    isEditing = false;
    
    // Show success message (you could add a toast notification here)
    alert('Profile updated successfully!');
  }

  function cancelEdit() {
    isEditing = false;
    // Reset form data to current user data
    if ($auth.user) {
      profileData = {
        name: $auth.user.name || '',
        email: $auth.user.email || '',
        phone: '',
        department: '',
        title: '',
        bio: ''
      };
    }
  }

  function changePassword() {
    // In a real app, this would open a password change modal or navigate to a password change page
    alert('Password change functionality would be implemented here.');
  }
</script>

<RoleGuard resource="profile" action="read" fallback="Please log in to view your profile.">
  <section class="profile">
    <div class="profile-header">
      <h1>My Profile</h1>
      <p>Manage your personal information and account settings</p>
    </div>

    <div class="profile-content">
      <div class="profile-card">
        <div class="profile-avatar">
          <div class="avatar-placeholder">
            {$auth.user?.name?.charAt(0) || 'U'}
          </div>
        </div>

        <div class="profile-info">
          <div class="info-section">
            <h3>Personal Information</h3>
            
            <div class="form-group">
              <label for="name">Full Name</label>
              {#if isEditing}
                <input 
                  type="text" 
                  id="name" 
                  bind:value={profileData.name} 
                  placeholder="Enter your full name"
                />
              {:else}
                <div class="info-value">{profileData.name || 'Not set'}</div>
              {/if}
            </div>

            <div class="form-group">
              <label for="email">Email Address</label>
              {#if isEditing}
                <input 
                  type="email" 
                  id="email" 
                  bind:value={profileData.email} 
                  placeholder="Enter your email"
                  readonly
                />
                <small class="help-text">Email cannot be changed</small>
              {:else}
                <div class="info-value">{profileData.email}</div>
              {/if}
            </div>

            <div class="form-group">
              <label for="phone">Phone Number</label>
              {#if isEditing}
                <input 
                  type="tel" 
                  id="phone" 
                  bind:value={profileData.phone} 
                  placeholder="Enter your phone number"
                />
              {:else}
                <div class="info-value">{profileData.phone || 'Not set'}</div>
              {/if}
            </div>
          </div>

          <div class="info-section">
            <h3>Professional Information</h3>
            
            <div class="form-group">
              <label for="title">Job Title</label>
              {#if isEditing}
                <input 
                  type="text" 
                  id="title" 
                  bind:value={profileData.title} 
                  placeholder="Enter your job title"
                />
              {:else}
                <div class="info-value">{profileData.title || 'Not set'}</div>
              {/if}
            </div>

            <div class="form-group">
              <label for="department">Department</label>
              {#if isEditing}
                <input 
                  type="text" 
                  id="department" 
                  bind:value={profileData.department} 
                  placeholder="Enter your department"
                />
              {:else}
                <div class="info-value">{profileData.department || 'Not set'}</div>
              {/if}
            </div>

            <div class="form-group">
              <label for="bio">Bio</label>
              {#if isEditing}
                <textarea 
                  id="bio" 
                  bind:value={profileData.bio} 
                  placeholder="Tell us about yourself"
                  rows="3"
                ></textarea>
              {:else}
                <div class="info-value">{profileData.bio || 'No bio added'}</div>
              {/if}
            </div>
          </div>

          <div class="info-section">
            <h3>Account Information</h3>
            
            <div class="form-group">
              <label>Role</label>
              <div class="info-value">
                <span class="role-badge {$auth.user?.role}">{$auth.user?.role}</span>
              </div>
            </div>

            <div class="form-group">
              <label>Account Status</label>
              <div class="info-value">
                <span class="status-badge active">Active</span>
              </div>
            </div>
          </div>
        </div>
      </div>

      <div class="profile-actions">
        {#if isEditing}
          <button class="save-btn" on:click={saveProfile}>Save Changes</button>
          <button class="cancel-btn" on:click={cancelEdit}>Cancel</button>
        {:else}
          <button class="edit-btn" on:click={startEditing}>Edit Profile</button>
          <button class="password-btn" on:click={changePassword}>Change Password</button>
        {/if}
      </div>
    </div>
  </section>
</RoleGuard>

<style>
  .profile {
    max-width: 800px;
    margin: 0 auto;
    padding: 2rem 0;
  }

  .profile-header {
    text-align: center;
    margin-bottom: 2rem;
  }

  .profile-header h1 {
    font-size: 2rem;
    margin-bottom: 0.5rem;
    color: #333;
  }

  .profile-header p {
    color: #666;
    font-size: 1.1rem;
  }

  .profile-content {
    background: white;
    border-radius: 12px;
    box-shadow: 0 4px 12px rgba(0,0,0,0.1);
    overflow: hidden;
  }

  .profile-card {
    padding: 2rem;
  }

  .profile-avatar {
    text-align: center;
    margin-bottom: 2rem;
  }

  .avatar-placeholder {
    width: 100px;
    height: 100px;
    border-radius: 50%;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 2.5rem;
    font-weight: bold;
    margin: 0 auto;
  }

  .profile-info {
    display: flex;
    flex-direction: column;
    gap: 2rem;
  }

  .info-section h3 {
    color: #333;
    margin-bottom: 1rem;
    padding-bottom: 0.5rem;
    border-bottom: 2px solid #f0f0f0;
  }

  .form-group {
    margin-bottom: 1.5rem;
  }

  .form-group label {
    display: block;
    font-weight: 500;
    color: #333;
    margin-bottom: 0.5rem;
  }

  .form-group input,
  .form-group textarea {
    width: 100%;
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
    transition: border-color 0.2s;
  }

  .form-group input:focus,
  .form-group textarea:focus {
    outline: none;
    border-color: #667eea;
    box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);
  }

  .form-group input[readonly] {
    background: #f8f9fa;
    color: #666;
  }

  .help-text {
    font-size: 0.875rem;
    color: #666;
    margin-top: 0.25rem;
  }

  .info-value {
    padding: 0.75rem;
    background: #f8f9fa;
    border-radius: 6px;
    color: #333;
    min-height: 1rem;
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

  .profile-actions {
    padding: 1.5rem 2rem;
    background: #f8f9fa;
    border-top: 1px solid #e9ecef;
    display: flex;
    gap: 1rem;
    justify-content: flex-end;
  }

  .edit-btn,
  .save-btn {
    background: #667eea;
    color: white;
    border: none;
    padding: 0.75rem 1.5rem;
    border-radius: 6px;
    cursor: pointer;
    font-size: 1rem;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .edit-btn:hover,
  .save-btn:hover {
    background: #5a6fd8;
  }

  .cancel-btn {
    background: #6c757d;
    color: white;
    border: none;
    padding: 0.75rem 1.5rem;
    border-radius: 6px;
    cursor: pointer;
    font-size: 1rem;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .cancel-btn:hover {
    background: #545b62;
  }

  .password-btn {
    background: #28a745;
    color: white;
    border: none;
    padding: 0.75rem 1.5rem;
    border-radius: 6px;
    cursor: pointer;
    font-size: 1rem;
    font-weight: 500;
    transition: background-color 0.2s;
  }

  .password-btn:hover {
    background: #218838;
  }

  @media (max-width: 768px) {
    .profile-actions {
      flex-direction: column;
    }
    
    .profile-actions button {
      width: 100%;
    }
  }
</style> 