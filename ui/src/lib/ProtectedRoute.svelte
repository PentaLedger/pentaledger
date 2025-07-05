<script>
  import { auth } from '$lib/auth';
  import { onMount } from 'svelte';
  import { goto } from '$app/navigation';
  
  let mounted = false;
  
  onMount(() => {
    mounted = true;
  });
  
  $: if (mounted && !$auth.isAuthenticated) {
    goto('/login');
  }
</script>

{#if mounted && $auth.isAuthenticated}
  <slot />
{:else if mounted}
  <div class="loading">
    <p>Redirecting to login...</p>
  </div>
{/if}

<style>
  .loading {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
    font-size: 1.1rem;
    color: #666;
  }
</style> 