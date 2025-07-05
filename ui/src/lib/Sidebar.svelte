<script>
  import { auth } from './auth';
  import { getAccessiblePages } from './roles';
  
  // Get accessible pages for current user
  $: accessiblePages = $auth.user ? getAccessiblePages($auth.user.role) : [];
</script>

<aside class="sidebar">
  <nav>
    <ul>
      {#each accessiblePages as page}
        <li><a href={page.path}>{page.label}</a></li>
      {/each}
    </ul>
  </nav>
</aside>

<style>
.sidebar {
  width: 220px;
  height: 100vh;
  background: #222;
  color: #fff;
  padding: 1rem 0;
  position: fixed;
  top: 0;
  left: 0;
  display: flex;
  flex-direction: column;
}
.sidebar nav ul {
  list-style: none;
  padding: 0;
  margin: 0;
}
.sidebar nav ul li {
  margin: 0.5rem 0;
}
.sidebar nav ul li a {
  color: #fff;
  text-decoration: none;
  padding: 0.25rem 1.5rem;
  display: block;
  border-radius: 4px;
  transition: background 0.2s;
  font-size: 0.9rem;
  line-height: 1.2;
}
.sidebar nav ul li a:hover {
  background: #444;
}
</style> 