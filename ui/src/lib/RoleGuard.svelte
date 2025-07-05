<script>
  import { auth } from './auth';
  import { hasPermission, canAccessPage } from './roles';
  
  export let resource = '';
  export let action = '';
  export let pagePath = '';
  export let requiredRole = '';
  export let fallback = "You don't have permission to access this content.";
  
  // Check if user has permission
  $: hasAccess = $auth.user && (
    (resource && action && hasPermission($auth.user.role, resource, action)) ||
    (pagePath && canAccessPage($auth.user.role, pagePath)) ||
    (requiredRole && $auth.user.role === requiredRole)
  );
</script>

{#if hasAccess}
  <slot />
{:else}
  <div class="permission-denied">
    <div class="permission-content">
      <h3>Access Denied</h3>
      <p>{fallback}</p>
      <p class="user-role">Your role: {$auth.user?.role || 'Unknown'}</p>
    </div>
  </div>
{/if}

<style>
  .permission-denied {
    display: flex;
    justify-content: center;
    align-items: center;
    min-height: 400px;
    padding: 2rem;
  }
  
  .permission-content {
    text-align: center;
    background: #fff;
    padding: 2rem;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    max-width: 400px;
  }
  
  .permission-content h3 {
    color: #dc3545;
    margin-bottom: 1rem;
  }
  
  .permission-content p {
    color: #666;
    margin-bottom: 0.5rem;
  }
  
  .user-role {
    font-size: 0.9rem;
    color: #999;
    font-style: italic;
  }
</style> 