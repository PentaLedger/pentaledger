import { writable } from 'svelte/store';
import { browser } from '$app/environment';
import type { UserRole } from './roles';

// Define types
interface User {
  email: string;
  name: string;
  role: UserRole;
}

interface AuthState {
  user: User | null;
  isAuthenticated: boolean;
  isLoading: boolean;
}

// Create authentication store
export const auth = writable<AuthState>({
  user: null,
  isAuthenticated: false,
  isLoading: false
});

// Mock user data for demonstration with different roles
const mockUsers = [
  { email: 'admin@pentaledger.com', password: 'admin123', name: 'Admin User', role: 'admin' as UserRole },
  { email: 'manager@pentaledger.com', password: 'manager123', name: 'Manager User', role: 'manager' as UserRole },
  { email: 'accountant@pentaledger.com', password: 'accountant123', name: 'Accountant User', role: 'accountant' as UserRole },
  { email: 'user@pentaledger.com', password: 'user123', name: 'Regular User', role: 'user' as UserRole }
];

// Login function
export async function login(email: string, password: string) {
  auth.update(state => ({ ...state, isLoading: true }));
  
  try {
    // Simulate API call delay
    await new Promise(resolve => setTimeout(resolve, 1000));
    
    // Check credentials (in real app, this would be an API call)
    const user = mockUsers.find(u => u.email === email && u.password === password);
    
    if (user) {
      // Store user data (in real app, you'd store a JWT token)
      const userData: User = { email: user.email, name: user.name, role: user.role };
      
      // Only access localStorage in browser
      if (browser) {
        localStorage.setItem('user', JSON.stringify(userData));
      }
      
      auth.update(state => ({
        ...state,
        user: userData,
        isAuthenticated: true,
        isLoading: false
      }));
      
      return { success: true };
    } else {
      throw new Error('Invalid credentials');
    }
  } catch (error) {
    auth.update(state => ({ ...state, isLoading: false }));
    return { success: false, error: error instanceof Error ? error.message : 'Unknown error' };
  }
}

// Logout function
export function logout() {
  // Only access localStorage in browser
  if (browser) {
    localStorage.removeItem('user');
  }
  
  auth.update(state => ({
    ...state,
    user: null,
    isAuthenticated: false
  }));
}

// Check if user is already logged in (on app startup)
export function checkAuth() {
  // Only access localStorage in browser
  if (!browser) return;
  
  const storedUser = localStorage.getItem('user');
  if (storedUser) {
    try {
      const userData: User = JSON.parse(storedUser);
      auth.update(state => ({
        ...state,
        user: userData,
        isAuthenticated: true
      }));
    } catch (error) {
      console.error('Error parsing stored user data:', error);
      localStorage.removeItem('user');
    }
  }
}

// Initialize auth check on import (only in browser)
if (browser) {
  checkAuth();
} 