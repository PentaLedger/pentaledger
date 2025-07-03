<script>
    import Sidebar from '../lib/Sidebar.svelte';
    import Navbar from '../lib/Navbar.svelte';
    import "../app.css";
    import '@fortawesome/fontawesome-free/css/all.min.css';
</script>

<Navbar />
<div class="layout">
  <Sidebar />
  <main>
    <slot />
  </main>
</div>

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