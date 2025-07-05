// Define user roles
export type UserRole = 'admin' | 'user' | 'manager' | 'accountant';

// Define permissions
export interface Permission {
  resource: string;
  actions: string[];
}

// Define role permissions
export const ROLE_PERMISSIONS: Record<UserRole, Permission[]> = {
  admin: [
    { resource: 'dashboard', actions: ['read'] },
    { resource: 'profile', actions: ['read', 'write'] },
    { resource: 'companies', actions: ['read', 'write', 'delete'] },
    { resource: 'governance', actions: ['read', 'write', 'delete'] },
    { resource: 'customers', actions: ['read', 'write', 'delete'] },
    { resource: 'invoices', actions: ['read', 'write', 'delete'] },
    { resource: 'quotes', actions: ['read', 'write', 'delete'] },
    { resource: 'vehicles', actions: ['read', 'write', 'delete'] },
    { resource: 'chart-of-accounts', actions: ['read', 'write', 'delete'] },
    { resource: 'expenses', actions: ['read', 'write', 'delete'] },
    { resource: 'vendors', actions: ['read', 'write', 'delete'] },
    { resource: 'payroll', actions: ['read', 'write', 'delete'] },
    { resource: 'taxes', actions: ['read', 'write', 'delete'] },
    { resource: 'reports', actions: ['read', 'write', 'delete'] },
    { resource: 'settings', actions: ['read', 'write', 'delete'] },
    { resource: 'user-management', actions: ['read', 'write', 'delete'] }
  ],
  manager: [
    { resource: 'dashboard', actions: ['read'] },
    { resource: 'profile', actions: ['read', 'write'] },
    { resource: 'companies', actions: ['read', 'write'] },
    { resource: 'governance', actions: ['read', 'write'] },
    { resource: 'customers', actions: ['read', 'write'] },
    { resource: 'invoices', actions: ['read', 'write'] },
    { resource: 'quotes', actions: ['read', 'write'] },
    { resource: 'vehicles', actions: ['read', 'write'] },
    { resource: 'chart-of-accounts', actions: ['read', 'write'] },
    { resource: 'expenses', actions: ['read', 'write'] },
    { resource: 'vendors', actions: ['read', 'write'] },
    { resource: 'payroll', actions: ['read', 'write'] },
    { resource: 'taxes', actions: ['read', 'write'] },
    { resource: 'reports', actions: ['read', 'write'] },
    { resource: 'settings', actions: ['read'] }
  ],
  accountant: [
    { resource: 'dashboard', actions: ['read'] },
    { resource: 'profile', actions: ['read', 'write'] },
    { resource: 'companies', actions: ['read'] },
    { resource: 'governance', actions: ['read'] },
    { resource: 'customers', actions: ['read'] },
    { resource: 'invoices', actions: ['read', 'write'] },
    { resource: 'quotes', actions: ['read'] },
    { resource: 'vehicles', actions: ['read'] },
    { resource: 'chart-of-accounts', actions: ['read', 'write'] },
    { resource: 'expenses', actions: ['read', 'write'] },
    { resource: 'vendors', actions: ['read'] },
    { resource: 'payroll', actions: ['read'] },
    { resource: 'taxes', actions: ['read', 'write'] },
    { resource: 'reports', actions: ['read'] },
    { resource: 'settings', actions: ['read'] }
  ],
  user: [
    { resource: 'dashboard', actions: ['read'] },
    { resource: 'profile', actions: ['read', 'write'] },
    { resource: 'companies', actions: ['read'] },
    { resource: 'governance', actions: ['read'] },
    { resource: 'customers', actions: ['read'] },
    { resource: 'invoices', actions: ['read'] },
    { resource: 'quotes', actions: ['read'] },
    { resource: 'vehicles', actions: ['read'] },
    { resource: 'chart-of-accounts', actions: ['read'] },
    { resource: 'expenses', actions: ['read'] },
    { resource: 'vendors', actions: ['read'] },
    { resource: 'payroll', actions: ['read'] },
    { resource: 'taxes', actions: ['read'] },
    { resource: 'reports', actions: ['read'] },
    { resource: 'settings', actions: ['read'] }
  ]
};

// Navigation items with role requirements
export const NAVIGATION_ITEMS = [
  { path: '/', label: 'Home', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/companies', label: 'Companies', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/governance', label: 'Governance/Compliance', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/customers', label: 'Customers', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/invoices', label: 'Invoices', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/quotes', label: 'Quotes', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/vehicles', label: 'Vehicles & Mileage', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/chart-of-accounts', label: 'Chart of Accounts', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/expenses', label: 'Expenses & Purchasing', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/vendors', label: 'Vendors and Suppliers', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/payroll', label: 'Payroll', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/taxes', label: 'Taxes', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/reports', label: 'Reports', roles: ['admin', 'manager', 'accountant', 'user'] },
  { path: '/settings', label: 'Settings', roles: ['admin', 'manager'] }
];

// Helper functions
export function hasPermission(userRole: UserRole, resource: string, action: string): boolean {
  const permissions = ROLE_PERMISSIONS[userRole];
  if (!permissions) return false;
  
  const resourcePermission = permissions.find(p => p.resource === resource);
  if (!resourcePermission) return false;
  
  return resourcePermission.actions.includes(action);
}

export function canAccessPage(userRole: UserRole, pagePath: string): boolean {
  const navItem = NAVIGATION_ITEMS.find(item => item.path === pagePath);
  if (!navItem) return false;
  
  return navItem.roles.includes(userRole);
}

export function getAccessiblePages(userRole: UserRole) {
  return NAVIGATION_ITEMS.filter(item => item.roles.includes(userRole));
} 