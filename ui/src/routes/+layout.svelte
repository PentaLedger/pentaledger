<script>
    import Sidebar from '../lib/Sidebar.svelte';
    import Navbar from '../lib/Navbar.svelte';
    import ProtectedRoute from '../lib/ProtectedRoute.svelte';
    import { page } from '$app/stores';
    import "../app.css";
    import '@fortawesome/fontawesome-free/css/all.min.css';
    
    // Check if current page is login
    $: isLoginPage = $page.url.pathname === '/login';
</script>

{#if isLoginPage}
  <slot />
{:else}
  <ProtectedRoute>
    <Navbar />
    <div class="layout">
      <Sidebar />
      <main>
        <slot />
      </main>
    </div>
  </ProtectedRoute>
{/if}

<style>
.layout {
  display: flex;
}
main {
  margin-left: 220px;
  padding: 2rem;
  flex: 1;
  margin-top: 60px;
}
</style>